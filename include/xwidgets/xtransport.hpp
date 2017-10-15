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

#include "xregistry.hpp"
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

    inline void xobject_comm_opened(xeus::xcomm&&, const xeus::xmessage&)
    {
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

        void send_patch(xeus::xjson&&) const;
        void send(xeus::xjson&&) const;

    protected:

        xtransport();
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
          m_hold(std::move(other.m_hold)),
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
        m_hold = std::move(other.m_hold);
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
        state[property.name()] = property();
        send_patch(std::move(state));
    }

    template <class D>
    inline void xtransport<D>::send_patch(xeus::xjson&& patch) const
    {
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;
        xeus::xjson data;
        data["method"] = "update";
        data["state"] = std::move(patch);
        data["buffer_paths"] = xeus::xjson::array();
        m_comm.send(std::move(metadata), std::move(data));
    }

    template <class D>
    inline void xtransport<D>::send(xeus::xjson&& content) const
    {
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;
        xeus::xjson data;
        data["method"] = "custom";
        data["content"] = std::move(content);
        m_comm.send(std::move(metadata), std::move(data));
    }

    template <class D>
    inline bool xtransport<D>::moved_from() const noexcept
    {
        return m_moved_from;
    }

    template <class D>
    inline void xtransport<D>::open()
    {
        xeus::xjson metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;
        xeus::xjson data;
        data["state"] = derived_cast().get_state();
        m_comm.open(std::move(metadata), std::move(data));
    }

    template <class D>
    inline void xtransport<D>::close()
    {
        m_comm.close(xeus::xjson::object(), xeus::xjson::object());
    }

    template <class D>
    inline void xtransport<D>::handle_message(const xeus::xmessage& message)
    {
        const xeus::xjson& content = message.content();
        const xeus::xjson& data = content["data"];
        std::string method = data["method"];
        if (method == "update")
        {
            auto it = data.find("state");
            if (it != data.end())
            {
                m_hold = &(it.value());
                derived_cast().apply_patch(it.value());
                m_hold = nullptr;
            }
        }
        else if (method == "request_state")
        {
            send_patch(derived_cast().get_state());
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
        // TODO: directly convert from xjson
        //std::string prefixed_guid = j;
        //auto guid = prefixed_guid.substr(10).c_str();
        //auto& holder = get_transport_registry().find(guid);
        //o = holder.template get<D>();  // TODO: move?
    }
}

#endif
