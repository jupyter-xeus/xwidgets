/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_COMMON_HPP
#define XWIDGETS_COMMON_HPP

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <xeus/xcomm.hpp>
#include <xproperty/xobserved.hpp>

#include "xbinary.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
#define REGISTER_PROPERTIES(...) \
    ([](auto* self, auto&&... args){ \
        (self->register_property(args), ...); \
    })(static_cast<derived_type*>(this), __VA_ARGS__);

    /**********************************************
     * property serialization and deserialization *
     **********************************************/

    // Values

    template <class T>
    inline void xwidgets_serialize(const T& value, nl::json& j, xeus::buffer_sequence&)
    {
        j = value;
    }

    // Specialization for binary buffers

    inline void xwidgets_serialize(const std::vector<char>& value, nl::json& j, xeus::buffer_sequence& buffers)
    {
        j = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.push_back(value);
    }

    template <class T>
    inline void xwidgets_deserialize(T& value, const nl::json& j, const xeus::buffer_sequence&)
    {
        value = j.template get<T>();
    }

    template <>
    inline void
    xwidgets_deserialize(std::vector<char>& value, const nl::json& j, const xeus::buffer_sequence& buffers)
    {
        std::size_t index = buffer_index(j.template get<std::string>());
        const auto& value_buffer = buffers[index];
        value.assign(value_buffer.data(), value_buffer.data() + value_buffer.size());
    }

    /***********************
     * xcommon declaration *
     ***********************/

    class XWIDGETS_API xcommon : public xp::xobserved
    {
    public:

        using observed_type = xp::xobserved;
        using patch_applier_type = std::function<void(const nl::json&, const xeus::buffer_sequence&)>;

        ~xcommon();

        xeus::xguid id() const noexcept;
        void display() const;
        std::vector<xjson_path_type>& buffer_paths();
        const std::vector<xjson_path_type>& buffer_paths() const;
        void register_patch_applier(const std::string& name, patch_applier_type&& applier);

        template <class P>
        void register_property(P& prop)
        {
            register_patch_applier(
                prop.name(),
                [&prop](const nl::json& value_json, const xeus::buffer_sequence& buffers)
                {
                    typename P::value_type value;
                    xwidgets_deserialize(value, value_json, buffers);
                    prop = value;
                }
            );
        }


    protected:

        xcommon();
        xcommon(xeus::xcomm&&);
        xcommon(const xcommon&);
        xcommon(xcommon&&);
        xcommon& operator=(const xcommon&);
        xcommon& operator=(xcommon&&);

        bool moved_from() const noexcept;
        void handle_custom_message(const nl::json&);
        void apply_patch_to_registered_properties(const nl::json& patch, const xeus::buffer_sequence& buffers);
        xeus::xcomm& comm();
        const xeus::xcomm& comm() const;
        const xeus::xmessage*& hold();
        const xeus::xmessage* const& hold() const;

        void open(nl::json&& patch, xeus::buffer_sequence&& buffers);
        void close();

        template <class T>
        void notify(const std::string& name, const T& value) const;
        void send(nl::json&&, xeus::buffer_sequence&&) const;
        void send_patch(nl::json&&, xeus::buffer_sequence&&, const char* method = "update") const;

        std::unordered_map<std::string, patch_applier_type> m_patch_appliers;

    private:

        template <class X, class Y>
        friend class xp::xproperty;

        /**
         * Indicate whether a global setting activates or deactivates ``echo_update`` messages.
         *
         * If the optional is empty, then no setting is set explicitly.
         */
        static std::optional<bool> global_echo_update();

        bool same_patch(
            const std::string&,
            const nl::json&,
            const xeus::buffer_sequence&,
            const nl::json&,
            const xeus::buffer_sequence&
        ) const;

        bool m_moved_from;
        const xeus::xmessage* m_hold;
        xeus::xcomm m_comm;
        std::vector<xjson_path_type> m_buffer_paths;
    };

    /**************************
     * to_json specialization *
     *************************/

    void XWIDGETS_API to_json(nl::json& j, const xcommon& o);

    /***********************************
     * mime_bundle_repr specialization *
     ***********************************/

    nl::json XWIDGETS_API mime_bundle_repr(const xcommon& val);

    /********************************************
     * xcommon template methods implementations *
     ********************************************/

    template <class T>
    inline void xcommon::notify(const std::string& name, const T& value) const
    {
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(value, state[name], buffers);
        const char* method = "update";

        // A current message is set, which implies that this change is triggered due to
        // a change from the frontend.
        if (m_hold != nullptr)
        {
            const auto& hold_state = m_hold->content()["data"]["state"];
            const auto& hold_buffers = m_hold->buffers();

            // The change that triggered this function is the same as the change coming from
            // the frontend so we need not send back an update but only an "echo_update" since
            // protocol 2.1.0
            auto const it = hold_state.find(name);
            if ((it != hold_state.end()) && same_patch(name, *it, hold_buffers, state[name], buffers))
            {
                // If the "echo_update" is explicitly deactivated we do not send the message
                auto const echo_update = global_echo_update();
                if (echo_update.has_value() && !echo_update.value())
                {
                    return;
                }
                // If the "echo_update" is explicitly activated or unspecified, we continue and
                // send message
                method = "echo_update";
            }
            // On the contrary, the update could differ from the change in the frontend.
            // For instance, if a validator adjusted the value of a property from the one
            // recieved from the frontend.
            // In this case, we need to send a regular "update" back to the frontend.
        }

        send_patch(std::move(state), std::move(buffers), method);
    }
}

#endif
