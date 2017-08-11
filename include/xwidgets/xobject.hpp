#ifndef XOBJECT_HPP
#define XOBJECT_HPP

#include <functional>
#include <list>
#include <string>
#include <type_traits>
#include <utility>

#include "xeus/xcomm.hpp"
#include "xeus/xinterpreter.hpp"

#include "xproperty/xobserved.hpp"
#include "xwidgets_config.hpp"

using namespace std::placeholders;

namespace xeus
{

    /**********************************
     * Comm target handling functions *
     **********************************/

    inline const char* get_widget_target_name()
    {
        return "jupyter.widget";
    }

    inline void xobject_comm_opened(const xcomm& /*comm*/, const xmessage& /*msg*/)
    {
    }

    inline int register_widget_target()
    {
        xeus::get_interpreter()
            .comm_manager()
        .register_comm_target(get_widget_target_name(), xeus::xobject_comm_opened);
        return 0;
    }

    inline xtarget* get_widget_target()
    {
        static int registered = register_widget_target();
        return ::xeus::get_interpreter().comm_manager().target(::xeus::get_widget_target_name());
    }

    inline const char* get_widget_protocol_version()
    {
        return "2.0.0";
    }

    /***********************
     * xobject declaration *
     ***********************/

    template <class D>
    class xobject : public xp::xobserved<D>
    {
    public:

        using message_callback_type = std::function<void(const xjson&)>;

        using base_type = xp::xobserved<D>;
        using derived_type = D;

        xobject();

        derived_type& derived_cast() & noexcept;
        const derived_type& derived_cast() const & noexcept;
        derived_type derived_cast() && noexcept;

        xguid id() const noexcept;
        void display() const;

        template <class P>
        void notify(const P& property) const;

        void send_patch(xjson&& state) const;

        XPROPERTY(std::string, derived_type, _model_module);
        XPROPERTY(std::string, derived_type, _model_module_version);
        XPROPERTY(std::string, derived_type, _model_name);
        XPROPERTY(std::string, derived_type, _view_module);
        XPROPERTY(std::string, derived_type, _view_module_version);
        XPROPERTY(std::string, derived_type, _view_name);

        xjson get_state() const;
        void apply_patch(const xjson& patch);

        void on_message(message_callback_type);

    protected:
        
        void open();

    private:
    
        void handle_message(const xmessage& message);
        void handle_custom_message(const xjson& content);
        void set_defaults();

        std::list<message_callback_type> m_message_callbacks;
        const xjson* m_hold;
        xcomm m_comm;
    };
    
    template <class D>
    void to_json(xjson& j, const xobject<D>& o);

    /**************************
     * xobject implementation *
     **************************/

    #define XOBJECT_SET_PROPERTY_FROM_PATCH(name, patch)                   \
    if (patch.find(#name) != patch.end())                                  \
    {                                                                      \
        name = patch.at(#name).get<typename decltype(name)::value_type>(); \
    }

    #define XOBJECT_SET_PATCH_FROM_PROPERTY(name, patch)                   \
        patch[#name] = this->name(); 

    // TODO: Generate an enum type with
    //  - operator=() allowing string assignment
    //  - to_json and from_json overload converting from and to the corresponding strings.
    #define X_CASELESS_STR_ENUM(...) std::string

    template <class D>
    inline xobject<D>::xobject()
        : m_comm(::xeus::get_widget_target(), xguid()), m_hold(nullptr)
    {
        m_comm.on_message(std::bind(&xobject::handle_message, this, _1));
        set_defaults();
    }

    template <class D>
    inline auto xobject<D>::derived_cast() & noexcept -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xobject<D>::derived_cast() const& noexcept -> const derived_type& 
    {
        return *static_cast<const derived_type*>(this);
    }
    
    template <class D>    
    inline auto xobject<D>::derived_cast() && noexcept -> derived_type
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xobject<D>::id() const noexcept -> xguid
    {
        return m_comm.id();
    }

    template <class D>
    inline void xobject<D>::display() const
    {
        xeus::xjson mime_bundle = R"(
        {
            "text/plain": "A Jupyter widget",
            "application/vnd.jupyter.widget-view+json": {
                "version_major": "2",
                "version_minor": "0"
            }
        }
        )"_json;

        mime_bundle["application/vnd.jupyter.widget-view+json"]["model_id"] = 
            xeus::guid_to_hex(this->derived_cast().id());
            
        ::xeus::get_interpreter().display_data(
            std::move(mime_bundle),
            xeus::xjson::object(),
            xeus::xjson::object()
        );
    }

    template <class D>
    template <class P>
    inline void xobject<D>::notify(const P& property) const
    {
        if (m_hold != nullptr)
        {
            auto it = m_hold->find(property.name());
            if (it != m_hold->end() && it.value() == property())
            {
                return;
            }
        }
        xjson state;
        state[property.name()] = property();
        send_patch(std::move(state));
    }

    template <class D>
    inline void xobject<D>::send_patch(xjson&& patch) const
    {
        xjson metadata;
        metadata["version"] = get_widget_protocol_version();
        xeus::xjson content;
        content["comm_id"] = xeus::guid_to_hex(this->derived_cast().id());
        content["data"] = R"({
            "method": "update"
        })"_json;
        content["data"]["state"] = patch;
        m_comm.target().publish_message("comm_msg", std::move(metadata), std::move(content));
    }

    template <class D>
    inline xjson xobject<D>::get_state() const
    {
        xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_module, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_module_version, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_name, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_module, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_module_version, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_name, state);
        return state;
    }

    template <class D>
    inline void xobject<D>::apply_patch(const xjson& patch)
    {
    }

    template <class D>
    inline void xobject<D>::on_message(message_callback_type cb)
    {
         m_message_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    inline void xobject<D>::open()
    {
        xjson metadata;
        metadata["version"] = get_widget_protocol_version();
        xeus::xjson data;
        data["state"] = derived_cast().get_state();
        m_comm.open(std::move(metadata), std::move(data));
    }

    template <class D>
    inline void xobject<D>::handle_message(const xmessage& message)
    {
        const xjson& content = message.content();
        const xjson& data = content["data"];
        std::string method = data["method"];
        if (method == "update")
        {
            auto it = data.find("state");
            if (it != data.end())
            {
                derived_cast().apply_patch(it.value());
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
                handle_custom_message(it.value());
            }
        }
    }

    template <class D>
    inline void xobject<D>::handle_custom_message(const xjson& content)
    {
        for (auto it = m_message_callbacks.begin(); it != m_message_callbacks.end(); ++it)
        {
            it->operator()(content);
        }
    }

    template <class D>
    inline void xobject<D>::set_defaults()
    {
        _model_module() = "jupyter-js-widgets";
        _model_module_version() = "~2.1.4";
        _model_name() = "WidgetModel";
        _view_module() = "jupyter-js-widgets";
        _view_module_version() = "~2.1.4";
        _view_name() = "WidgetView";
    }

    template <class D>
    inline void to_json(xjson& j, const xobject<D>& o)
    {
        j = "IPY_MODEL_" + guid_to_hex(o.id());
    }
}

#endif

