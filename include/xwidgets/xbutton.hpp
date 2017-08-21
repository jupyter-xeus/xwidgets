/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BUTTON_HPP
#define XWIDGETS_BUTTON_HPP

#include "xstyle.hpp"
#include "xwidget.hpp"

namespace xeus
{
    /****************************
     * button_style declaration *
     ****************************/

    template <class D>
    class xbutton_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        xbutton_style();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(std::string), derived_type, button_color);
        XPROPERTY(std::string, derived_type, font_weight);

    private:

        void set_defaults();
    };

    class button_style final : public xbutton_style<button_style>
    {
    public:

        using base_type = xbutton_style<button_style>;

        button_style()
            : base_type()
        {
            this->open();
        }

        ~button_style()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        button_style(const button_style& other)
            : base_type(other)
        {
            this->open();
        }

        button_style& operator=(const button_style& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /**********************
     * button declaration *
     **********************/

    template <class D>
    class xbutton : public xwidget<D>
    {
    public:

        using click_callback_type = std::function<void()>;

        using base_type = xwidget<D>;
        using derived_type = D;

        xbutton();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        void on_click(click_callback_type);

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(std::string, derived_type, tooltip);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(std::string, derived_type, icon);
        XPROPERTY(X_CASELESS_STR_ENUM(primary, success, info, warning, danger, ), derived_type, button_style);
        XPROPERTY(::xeus::button_style, derived_type, style);

        void handle_custom_message(const xjson&);

    private:

        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    class button final : public xbutton<button>
    {
    public:

        using base_type = xbutton<button>;

        button()
            : base_type()
        {
            this->open();
        }

        ~button()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        button(const button& other)
            : base_type(other)
        {
            this->open();
        }

        button& operator=(const button& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /********************************
     * xbutton_style implementation *
     ********************************/

    template <class D>
    inline xbutton_style<D>::xbutton_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xbutton_style<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(button_color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(font_weight, state);

        return state;
    }

    template <class D>
    inline void xbutton_style<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(button_color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(font_weight, patch);
    }

    template <class D>
    inline void xbutton_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ButtonStyleModel";
    }

    /**************************
     * xbutton implementation *
     **************************/

    template <class D>
    inline xbutton<D>::xbutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xbutton<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(description, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(icon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(button_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    template <class D>
    inline void xbutton<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(description, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(icon, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch);
    }

    template <class D>
    inline void xbutton<D>::on_click(click_callback_type cb)
    {
        m_click_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    inline void xbutton<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ButtonModel";
        this->_view_name() = "ButtonView";
    }

    template <class D>
    inline void xbutton<D>::handle_custom_message(const xjson& content)
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
