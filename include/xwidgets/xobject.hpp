#ifndef XOBJECT_HPP
#define XOBJECT_HPP

#include <functional>
#include <string>
#include <type_traits>
#include <utility>

#include "xeus/xcomm.hpp"
#include "xproperty/xobserved.hpp"

using namespace std::placeholders;

namespace xeus
{

    inline void xobject_comm_opened(const xcomm& comm, const xmessage& msg)
    {
    }

    template <class D>
    class xobject : public xp::xobserved<D>
    {
    public:

        using base_type = xp::xobserved<D>;
        using derived_type = D;

        inline derived_type& derived_cast() & noexcept
        {
            return *static_cast<derived_type*>(this);
        }

        inline const derived_type& derived_cast() const& noexcept
        {
            return *static_cast<const derived_type*>(this);
        }
        
        inline derived_type derived_cast() && noexcept
        {
            return *static_cast<derived_type*>(this);
        }

        xobject() : m_comm(get_interpreter().comm_manager().target(target_name), xguid())
        {
            m_comm.on_message(std::bind(&xobject::handle_message, this, _1));
            set_defaults();
        }

        inline xguid id() const noexcept
        {
            return m_comm.id();
        }

        inline void display() const
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
            
            get_interpreter().display_data(
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

            get_interpreter().comm_manager().target(target_name)->publish_message("comm_msg", xeus::xjson::object(), std::move(comm_display));  
        }

        template <class P>
        inline void notify(const P& property) const
        {
            xjson state;
            state[property.name()] = property.raw_value();
            send_state(std::move(state));
        }

        inline void send_state(xjson&& state) const
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
            get_interpreter().comm_manager().target(target_name)->publish_message("comm_msg", xeus::xjson::object(), std::move(data));  
        }

        // TODO: make these property optional (allow none)
        XPROPERTY(std::string, derived_type, _model_module);
        XPROPERTY(std::string, derived_type, _model_module_version);
        XPROPERTY(std::string, derived_type, _model_name);
        XPROPERTY(std::string, derived_type, _view_module);
        XPROPERTY(std::string, derived_type, _view_module_version);
        XPROPERTY(std::string, derived_type, _view_name);

        inline xjson get_state() const
        {
            xjson state;
            state["_model_module"] = _model_module.raw_value();
            state["_model_module_version"] = _model_module_version.raw_value();
            state["_model_name"] = _model_name.raw_value();
            state["_view_module"] = _view_module.raw_value();
            state["_view_module_version"] = _view_module_version.raw_value();
            state["_view_name"] = _view_name.raw_value();
            return state;
        }
        
        inline void set_state(const xjson& state)
        {
        }

    protected:
        
        inline void open()
        {
            m_comm.open(xjson::object(), derived_cast().get_state());
        }

    private:
    
        inline void handle_message(const xmessage& message)
        {
            const xjson& content = message.content();
            const xjson& data = content["data"];
            std::string method = data["method"];
            if (method == "backbone")
            {
                auto it = data.find("sync_data");
                if (it != data.end())
                {
                    derived_cast().set_state(it.value());
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
    
        inline void set_defaults()
        {
            _model_module.raw_value() = "jupyter-js-widgets";
            _model_module_version.raw_value() = "~2.1.4";
            _model_name.raw_value() = "WidgetModel";
            _view_module.raw_value() = "jupyter-js-widgets";
            _view_module_version.raw_value() = "~2.1.4";
            _view_name.raw_value() = "WidgetView";
        }

        xcomm m_comm;

        static const char* target_name;
    };

    // In the cpp (multiple inheritance)
    template <class D>
    const char* xeus::xobject<D>::target_name = "jupyter.widget";
    
    template <class D>
    void to_json(xjson& j, const xobject<D>& o)
    {
        j = "IPY_MODEL_" + guid_to_hex(o.id());
    }
}

#endif
