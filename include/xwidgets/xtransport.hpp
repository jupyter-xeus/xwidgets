/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TRANSPORT_HPP
#define XWIDGETS_TRANSPORT_HPP

#include <functional>
#include <list>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "xeus/xcomm.hpp"
#include "xeus/xinterpreter.hpp"

#include "xbinary.hpp"
#include "xfactory.hpp"
#include "xholder.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
    /**********************************
     * Comm target handling functions *
     **********************************/

    inline const char* get_widget_target_name()
    {
        return "jupyter.widget";
    }

    inline void xobject_comm_opened(xeus::xcomm&& comm, const xeus::xmessage& msg)
    {
        const nl::json& content = msg.content();
        const nl::json& metadata = msg.metadata();

        std::string version;
        try
        {
            version = metadata.at("version").get<std::string>();
        }
        catch (std::out_of_range)
        {
            version = "";
        }

        if (version.substr(0, version.find(".")) != XWIDGETS_STRINGIFY(XWIDGETS_PROTOCOL_VERSION_MAJOR))
        {
            throw std::runtime_error("Incompatible widget protocol versions");
        }

        const nl::json& data = content["data"];
        const nl::json& state = data["state"];
        const xeus::buffer_sequence& buffers = msg.buffers();

        xfactory& factory = get_xfactory();
        factory.make(std::move(comm), state, buffers);
    }

    inline int register_widget_target()
    {
        xeus::get_interpreter()
            .comm_manager()
            .register_comm_target(get_widget_target_name(), xobject_comm_opened);
        return 0;
    }

    inline xeus::xtarget* get_widget_target()
    {
        static int registered = register_widget_target();
        return ::xeus::get_interpreter()
            .comm_manager()
            .target(get_widget_target_name());
    }

    /**********************************************
     * property serialization and deserialization *
     **********************************************/

    // Values

    template <class T>
    inline void xwidgets_serialize(const T& value, nl::json& j, xeus::buffer_sequence&)
    {
        j = value;
    }

    template <class T>
    inline void xwidgets_deserialize(T& value, const nl::json& j, const xeus::buffer_sequence&)
    {
        value = j.template get<T>();
    }

    // Properties

    template <class P>
    inline void set_property_from_patch(P& property, const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            typename P::value_type value;
            xwidgets_deserialize(value, *it, buffers);
            property = value;
        }
    }

    /*******************************
     * base xtransport declaration *
     *******************************/

    template <class D>
    class xtransport
    {
    public:

        using derived_type = D;

        derived_type& derived_cast() & noexcept;
        const derived_type& derived_cast() const & noexcept;
        derived_type derived_cast() && noexcept;

        xeus::xguid id() const noexcept;
        void display() const;

        void send_patch(nl::json&&, xeus::buffer_sequence&&) const;
        void send(nl::json&&, xeus::buffer_sequence&&) const;

        const std::vector<xjson_path_type>& buffer_paths() const;

    protected:

        xtransport();
        xtransport(xeus::xcomm&&, bool owning = false);
        ~xtransport();
        xtransport(const xtransport&);
        xtransport(xtransport&&);
        xtransport& operator=(const xtransport&);
        xtransport& operator=(xtransport&&);

        bool moved_from() const noexcept;
        void open();
        void close();

        template <class P>
        void notify(const P& property) const;

    private:

        void handle_message(const xeus::xmessage&);
        void handle_custom_message(const nl::json&);

        bool same_patch(const std::string&,
                        const nl::json&,
                        const xeus::buffer_sequence&,
                        const nl::json&,
                        const xeus::buffer_sequence&) const;

        bool m_moved_from;
        const xeus::xmessage* m_hold;
        xeus::xcomm m_comm;
    };

    template <class T, class R = void>
    struct enable_xtransport
    {
        using type = std::enable_if_t<std::is_base_of<xtransport<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xtransport_t = typename enable_xtransport<T, R>::type;

    /****************************************
     * to_json and from_json specialization *
     ****************************************/

    template <class D>
    void to_json(nl::json& j, const xtransport<D>& o);

    template <class D>
    void from_json(const nl::json& j, xtransport<D>& o);

    /**********************************
     * base xtransport implementation *
     **********************************/

    template <class D>
    inline xtransport<D>::xtransport()
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(get_widget_target(), xeus::new_xguid())
    {
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
    }

    template <class D>
    inline xtransport<D>::~xtransport()
    {
        if (!m_moved_from)
        {
            get_transport_registry().unregister(this->id());
        }
    }

    template <class D>
    inline xtransport<D>::xtransport(xeus::xcomm&& comm, bool owning)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(std::move(comm))
    {
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        if (!owning)
        {
            get_transport_registry().register_weak(this);
        }
    }

    template <class D>
    inline xtransport<D>::xtransport(const xtransport& other)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(other.m_comm)
    {
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
    }

    template <class D>
    inline xtransport<D>::xtransport(xtransport&& other)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(std::move(other.m_comm))
    {
        other.m_moved_from = true;
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with `this`.
    }

    template <class D>
    inline xtransport<D>& xtransport<D>::operator=(const xtransport& other)
    {
        m_moved_from = false;
        get_transport_registry().unregister(this->id());
        m_hold = nullptr;
        m_comm = other.m_comm;
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
        return *this;
    }

    template <class D>
    inline xtransport<D>& xtransport<D>::operator=(xtransport&& other)
    {
        other.m_moved_from = true;
        m_moved_from = false;
        get_transport_registry().unregister(this->id());
        m_hold = nullptr;
        m_comm = std::move(other.m_comm);
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with `this`.
        return *this;
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() & noexcept -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() const & noexcept -> const derived_type&
    {
        return *static_cast<const derived_type*>(this);
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() && noexcept -> derived_type
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xtransport<D>::id() const noexcept -> xeus::xguid
    {
        return m_comm.id();
    }

    template <class D>
    inline void xtransport<D>::display() const
    {
        nl::json mime_bundle;

        // application/vnd.jupyter.widget-view+json
        nl::json widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = this->id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget";

        ::xeus::get_interpreter().display_data(
            std::move(mime_bundle),
            nl::json::object(),
            nl::json::object());
    }

    template <class D>
    template <class P>
    inline void xtransport<D>::notify(const P& property) const
    {
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(property(), state[property.name()], buffers);

        if (m_hold != nullptr)
        {
            const auto& hold_state = m_hold->content()["data"]["state"];
            const auto& hold_buffers = m_hold->buffers();

            auto it = hold_state.find(property.name());
            if (it != hold_state.end())
            {
                if(same_patch(property.name(),
                              *it,
                              hold_buffers,
                              state[property.name()],
                              buffers))
                {
                    return;
                }
            }
        }

        send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xtransport<D>::send_patch(nl::json&& patch, xeus::buffer_sequence&& buffers) const
    {
        // extract buffer paths
        auto paths = nl::json::array();
        extract_buffer_paths(derived_cast().buffer_paths(), patch, buffers, paths);

        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["method"] = "update";
        data["state"] = std::move(patch);
        data["buffer_paths"] = std::move(paths);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    template <class D>
    inline void xtransport<D>::send(nl::json&& content, xeus::buffer_sequence&& buffers) const
    {
        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["method"] = "custom";
        data["content"] = std::move(content);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    template <class D>
    inline const std::vector<xjson_path_type>& xtransport<D>::buffer_paths() const
    {
        static const std::vector<xjson_path_type> default_buffer_paths;
        return default_buffer_paths;
    }

    template <class D>
    inline bool xtransport<D>::moved_from() const noexcept
    {
        return m_moved_from;
    }

    template <class D>
    inline void xtransport<D>::open()
    {
        // extract buffer paths
        nl::json paths;
        nl::json state;
        xeus::buffer_sequence buffers;
        derived_cast().serialize_state(state, buffers);
        extract_buffer_paths(derived_cast().buffer_paths(), state, buffers, paths);

        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["state"] = std::move(state);
        data["buffer_paths"] = std::move(paths);

        m_comm.open(std::move(metadata), std::move(data), std::move(buffers));
    }

    template <class D>
    inline void xtransport<D>::close()
    {
        m_comm.close(nl::json::object(), nl::json::object(), xeus::buffer_sequence());
    }

    template <class D>
    inline void xtransport<D>::handle_message(const xeus::xmessage& message)
    {
        const nl::json& content = message.content();
        const nl::json& data = content["data"];
        std::string method = data["method"];
        if (method == "update")
        {
            const nl::json& state = data["state"];
            const auto& buffers = message.buffers();
            const nl::json& buffer_paths = data["buffer_paths"];
            m_hold = std::addressof(message);;
            insert_buffer_paths(const_cast<nl::json&>(state), buffer_paths);
            derived_cast().apply_patch(state, buffers);
            m_hold = nullptr;
        }
        else if (method == "request_state")
        {
            nl::json state;
            xeus::buffer_sequence buffers;
            derived_cast().serialize_state(state, buffers);
            send_patch(std::move(state), std::move(buffers));
        }
        else if (method == "custom")
        {
            auto it = data.find("content");
            if (it != data.end())
            {
                derived_cast().handle_custom_message(it.value());
            }
        }
    }

    template <class D>
    inline void xtransport<D>::handle_custom_message(const nl::json& /*content*/)
    {
    }

    template <class D>
    inline bool xtransport<D>::same_patch(const std::string& name,
                                          const nl::json& j1,
                                          const xeus::buffer_sequence&,
                                          const nl::json& j2,
                                          const xeus::buffer_sequence&) const
         {
             const auto& paths = derived_cast().buffer_paths();
             // For a widget with no binary buffer, compare the patches
             if (paths.empty())
             {
                 return j1 == j2;
             }
             else
             {
                 // For a property with no binary buffer, compare the patches
                 if (std::find_if(paths.cbegin(), paths.cend(), [name](const auto& v) {
                     return !v.empty() && v[0] == name;
                 }) == paths.cend())
                 {
                    return j1 == j2;
                 }
                 else
                 {
                     // TODO: handle the comparison of binary buffers.
                     return true;
                 }
             }
         }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    template <class D>
    inline void to_json(nl::json& j, const xtransport<D>& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    template <class D>
    inline void from_json(const nl::json& j, xtransport<D>& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        auto& holder = get_transport_registry().find(guid);
        o.derived_cast() = std::move(holder.template get<D>());
    }
}

#endif
