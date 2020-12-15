/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_COMMON_HPP
#define XWIDGETS_COMMON_HPP

#include <string>
#include <utility>
#include <vector>

#include "xeus/xcomm.hpp"

#include "xbinary.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
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
        buffers.emplace_back(value.data(), value.size());
    }

    template <class T>
    inline void xwidgets_deserialize(T& value, const nl::json& j, const xeus::buffer_sequence&)
    {
        value = j.template get<T>();
    }

    /***********************
     * xcommon declaration *
     ***********************/

    class XWIDGETS_API xcommon
    {
    public:

        xeus::xguid id() const noexcept;
        void display() const;

    protected:

        xcommon();
        xcommon(xeus::xcomm&&);
        ~xcommon();
        xcommon(const xcommon&);
        xcommon(xcommon&&);
        xcommon& operator=(const xcommon&);
        xcommon& operator=(xcommon&&);

        bool moved_from() const noexcept;
        void handle_custom_message(const nl::json&);
        xeus::xcomm& comm();
        const xeus::xcomm& comm() const;
        const xeus::xmessage*& hold();
        const xeus::xmessage* const& hold() const;
        std::vector<xjson_path_type>& buffer_paths();
        const std::vector<xjson_path_type>& buffer_paths() const;

        void open(nl::json&& patch, xeus::buffer_sequence&& buffers);
        void close();

        template <class T>
        void notify(const std::string& name, const T& value) const;
        void send(nl::json&&, xeus::buffer_sequence&&) const;
        void send_patch(nl::json&&, xeus::buffer_sequence&&) const;

    private:

        bool same_patch(const std::string&,
                        const nl::json&,
                        const xeus::buffer_sequence&,
                        const nl::json&,
                        const xeus::buffer_sequence&) const;

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

        if (m_hold != nullptr)
        {
            const auto& hold_state = m_hold->content()["data"]["state"];
            const auto& hold_buffers = m_hold->buffers();

            auto it = hold_state.find(name);
            if (it != hold_state.end())
            {
                if(same_patch(name,
                              *it,
                              hold_buffers,
                              state[name],
                              buffers))
                {
                    return;
                }
            }
        }

        send_patch(std::move(state), std::move(buffers));
    }
}

#endif
