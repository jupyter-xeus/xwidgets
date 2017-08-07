#ifndef XOBJECT_HPP
#define XOBJECT_HPP

#include <functional>
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
    inline const char* get_widget_target_name()
    {
        return "jupyter.widget";
    }

    inline xtarget* get_widget_target()
    {
        return ::xeus::get_interpreter().comm_manager().target(::xeus::get_widget_target_name());
    }

    inline void xobject_comm_opened(const xcomm& /*comm*/, const xmessage& /*msg*/)
    {
    }

    template <class D>
    class xobject : public xp::xobserved<D>
    {
    public:

        using base_type = xp::xobserved<D>;
        using derived_type = D;

        xobject();

        derived_type& derived_cast() & noexcept;
        const derived_type& derived_cast() const& noexcept;
        derived_type derived_cast() && noexcept;

        xguid id() const noexcept;
        void display() const;

        template <class P>
        void notify(const P& property) const;

        void send_state(xjson&& state) const;

        // TODO: make these property optional (allow none)
        XPROPERTY(std::string, derived_type, _model_module);
        XPROPERTY(std::string, derived_type, _model_module_version);
        XPROPERTY(std::string, derived_type, _model_name);
        XPROPERTY(std::string, derived_type, _view_module);
        XPROPERTY(std::string, derived_type, _view_module_version);
        XPROPERTY(std::string, derived_type, _view_name);

        xjson get_state() const;
        void set_state(const xjson& state);

    protected:
        
        void open();

    private:
    
        void handle_message(const xmessage& message);
        void set_defaults();

        const xjson* m_hold;
        xcomm m_comm;
    };
    
    template <class D>
    void to_json(xjson& j, const xobject<D>& o);

    /**************************
     * xobject implementation *
     **************************/

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
        xeus::xjson display_data = R"(
        {
            "application/vnd.jupyter.widget-view+json": {
                "version_major": "2",
                "version_minor": "0"
            }
        }
        )"_json;

        display_data["application/vnd.jupyter.widget-view+json"]["model_id"] = 
            xeus::guid_to_hex(this->derived_cast().id());
            
        ::xeus::get_interpreter().display_data(
            std::move(display_data),
            xeus::xjson::object(),
            xeus::xjson::object()
        );
            
        xeus::xjson comm_display = R"(
        {
            "data": {
                "method": "display"
            }
        }
        )"_json;

        comm_display["comm_id"] =  xeus::guid_to_hex(this->derived_cast().id());

        ::xeus::get_interpreter().comm_manager().target(::xeus::get_widget_target_name())->publish_message("comm_msg", xeus::xjson::object(), std::move(comm_display));  
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
        send_state(std::move(state));
    }

    template <class D>
    inline void xobject<D>::send_state(xjson&& state) const
    {
        xeus::xjson data = R"(
        {
            "data": {
                "method": "update"
            }
        }
        )"_json;

        data["comm_id"] =  xeus::guid_to_hex(this->derived_cast().id());
        data["data"]["state"] = state;
        ::xeus::get_widget_target()->publish_message("comm_msg", xeus::xjson::object(), std::move(data));
    }

    template <class D>
    inline xjson xobject<D>::get_state() const
    {
        xjson state;
        state["_model_module"] = _model_module();
        state["_model_module_version"] = _model_module_version();
        state["_model_name"] = _model_name();
        state["_view_module"] = _view_module();
        state["_view_module_version"] = _view_module_version();
        state["_view_name"] = _view_name();
        return state;
    }

    template <class D>
    inline void xobject<D>::set_state(const xjson& state)
    {
    }

    template <class D>
    inline void xobject<D>::open()
    {
        m_comm.open(xjson::object(), derived_cast().get_state());
    }

    template <class D>
    inline void xobject<D>::handle_message(const xmessage& message)
    {
        const xjson& content = message.content();
        const xjson& data = content["data"];
        std::string method = data["method"];
        if (method == "backbone")
        {
            auto it = data.find("sync_data");
            if (it != data.end())
            {
                m_hold = &(it.value());
                derived_cast().set_state(it.value());
                m_hold = nullptr;
            }
        }
        else if (method == "request_state")
        {
            send_state(derived_cast().get_state());
        }
        else if (method == "custom")
        {
            auto it = data.find("content");
            if (it != data.end())
            {
                // handle_custom_msg(it.value());
            }
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

