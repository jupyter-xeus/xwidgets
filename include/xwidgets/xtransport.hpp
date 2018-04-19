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
        const xeus::xjson& content = msg.content();
        const xeus::xjson& metadata = msg.metadata();

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

        const xeus::xjson& data = content["data"];
        const xeus::xjson& state = data["state"];
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

    /*****************
     * Serialization *
     *****************/

    template <class T>
    inline void xwidgets_serialize(const T& value, xeus::xjson& patch, xeus::buffer_sequence&, const std::string& name)
    {
        patch[name] = value;
    }

    template <class T>
    inline void xwidgets_deserialize(T& value, const xeus::xjson& j, const xeus::buffer_sequence&)
    {
        value = j.template get<T>();
    }

    /*******************************
     * base xtransport declaration *
     *******************************/

    template <class D>
    class xtransport
    {
    public:

        using message_callback_type = std::function<void(const xeus::xjson&)>;

        using derived_type = D;

        derived_type& derived_cast() & noexcept;
        const derived_type& derived_cast() const & noexcept;
        derived_type derived_cast() && noexcept;

        xeus::xguid id() const noexcept;
        void display() const;

        void send_patch(xeus::xjson&&, xeus::buffer_sequence&&) const;
        void send(xeus::xjson&&, xeus::buffer_sequence&&) const;

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

        template <class P>
        void set_patch_from_property(const P&, xeus::xjson&, xeus::buffer_sequence&) const;

        template <class P>
        void set_property_from_patch(P&, const xeus::xjson&, const xeus::buffer_sequence&);

    private:

        void handle_message(const xeus::xmessage&);
        void handle_custom_message(const xeus::xjson&);

        bool m_moved_from;
        std::list<message_callback_type> m_message_callbacks;
        const xeus::xjson* m_hold;
        xeus::xcomm m_comm;
    };

    /****************************************
     * to_json and from_json specialization *
     ****************************************/

    template <class D>
    void to_json(xeus::xjson& j, const xtransport<D>& o);

    template <class D>
    void from_json(const xeus::xjson& j, xtransport<D>& o);

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
          m_message_callbacks(other.m_message_callbacks),
          m_hold(nullptr),
          m_comm(other.m_comm)
    {
        m_comm.on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
    }

    template <class D>
    inline xtransport<D>::xtransport(xtransport&& other)
        : m_moved_from(false),
          m_message_callbacks(std::move(other.m_message_callbacks)),
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
        m_message_callbacks = other.m_message_callbacks;
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
        m_message_callbacks = std::move(other.m_message_callbacks);
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
        xeus::xjson mime_bundle;

        // application/vnd.jupyter.widget-view+json
        xeus::xjson widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = this->id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget";

        ::xeus::get_interpreter().display_data(
            std::move(mime_bundle),
            xeus::xjson::object(),
            xeus::xjson::object());
    }

    template <class D>
    template <class P>
    inline void xtransport<D>::notify(const P& property) const
    {
        if (m_hold != nullptr)
        {
            auto it = m_hold->find(property.name());
            if (it != m_hold->end() && it.value() == property())
            {
                return;
            }
        }

        xeus::xjson state;
        xeus::buffer_sequence buffers;
        set_patch_from_property(property, state, buffers);
        send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class P>
    inline void xtransport<D>::set_patch_from_property(const P& property, xeus::xjson& patch, xeus::buffer_sequence& buffers) const
    {
        derived_cast().set_patch_from_property_impl(property, patch, buffers);
    }

    template <class D>
    template <class P>
    inline void xtransport<D>::set_property_from_patch(P& property, const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        derived_cast().set_property_from_patch_impl(property, patch, buffers);
    }

    template <class D>
    inline void xtransport<D>::send_patch(xeus::xjson&& patch, xeus::buffer_sequence&& buffers) const
    {
        // extract buffer paths
        auto paths = xeus::xjson::array();
        extract_buffer_paths(derived_cast().buffer_paths(), patch, buffers, paths);

        // metadata
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        xeus::xjson data;
        data["method"] = "update";
        data["state"] = std::move(patch);
        data["buffer_paths"] = std::move(paths);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    template <class D>
    inline void xtransport<D>::send(xeus::xjson&& content, xeus::buffer_sequence&& buffers) const
    {
        // metadata
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        xeus::xjson data;
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
        xeus::xjson paths;
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        derived_cast().serialize_state(state, buffers);
        extract_buffer_paths(derived_cast().buffer_paths(), state, buffers, paths);

        // metadata
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        xeus::xjson data;
        data["state"] = std::move(state);
        data["buffer_paths"] = std::move(paths);

        m_comm.open(std::move(metadata), std::move(data), std::move(buffers));
    }

    template <class D>
    inline void xtransport<D>::close()
    {
        m_comm.close(xeus::xjson::object(), xeus::xjson::object(), xeus::buffer_sequence());
    }

    template <class D>
    inline void xtransport<D>::handle_message(const xeus::xmessage& message)
    {
        const xeus::xjson& content = message.content();
        const xeus::xjson& data = content["data"];
        std::string method = data["method"];
        const xeus::buffer_sequence& buffers = message.buffers();
        if (method == "update")
        {
            const xeus::xjson& state = data["state"];
            const xeus::xjson& buffer_paths = data["buffer_paths"];
            m_hold = &(state);
            insert_buffer_paths(const_cast<xeus::xjson&>(state), buffer_paths);
            derived_cast().apply_patch(state, buffers);
            m_hold = nullptr;
        }
        else if (method == "request_state")
        {
            xeus::xjson state;
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
    inline void xtransport<D>::handle_custom_message(const xeus::xjson& /*content*/)
    {
    }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    template <class D>
    inline void to_json(xeus::xjson& j, const xtransport<D>& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    template <class D>
    inline void from_json(const xeus::xjson& j, xtransport<D>& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        auto& holder = get_transport_registry().find(guid);
        o.derived_cast() = std::move(holder.template get<D>());
    }
}

#endif
