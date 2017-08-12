#ifndef XBUTTON_HPP
#define XBUTTON_HPP

#include "xwidget.hpp"

namespace xeus
{
    class xbutton final : public xwidget<xbutton>
    {
    public:

        using click_callback_type = std::function<void()>;

        using base_type = xwidget<xbutton>;

        xbutton();

        xjson get_state() const;
        void apply_patch(const xjson& patch);

        void on_click(std::function<void()>);

        XPROPERTY(std::string, xbutton, description);
        XPROPERTY(std::string, xbutton, tooltip);
        XPROPERTY(bool, xbutton, disabled);
        XPROPERTY(std::string, xbutton, icon);
        XPROPERTY(X_CASELESS_STR_ENUM(primary, success, info, warning, danger,), xbutton, button_style);
        //XPROPERTY(xbutton_style, xbutton, style);

    private:

        void handle_button_message(const xjson&);
        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    /**************************
     * xbutton implementation *
     **************************/

    inline xbutton::xbutton()
        : base_type()
    {
        set_defaults();
        this->on_message(std::bind(&xbutton::handle_button_message, this, _1));
        this->open();
    }

    inline xjson xbutton::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(description, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(icon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(button_style, state);
        // XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    inline void xbutton::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(description, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(icon, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_style, patch);
        // XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch);
    }

    inline void xbutton::on_click(click_callback_type cb)
    {
        m_click_callbacks.emplace_back(std::move(cb));
    }

    inline void xbutton::set_defaults()
    {
        base_type::_model_module() = "@jupyter-widgets/controls";
        base_type::_view_module() = "@jupyter-widgets/controls";
        base_type::_model_name() = "ButtonModel";
        base_type::_view_name() = "ButtonView";
    }

    inline void xbutton::handle_button_message(const xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "click")
        {
            for (auto it = m_click_callbacks.begin(); it != m_click_callbacks.end(); ++it)
            {
                it->operator()();
            }
        }
    }
}
#endif

