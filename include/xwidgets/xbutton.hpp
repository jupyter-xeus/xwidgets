/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BUTTON_HPP
#define XWIDGETS_BUTTON_HPP

#include <functional>
#include <list>
#include <stdexcept>
#include <string>
#include <utility>

#include "xtl/xoptional.hpp"

#include "xcolor.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xstyle.hpp"
#include "xwidget.hpp"

namespace xw
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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(xtl::xoptional<html_color>, derived_type, button_color);
        XTRAIT(std::string, derived_type, font_weight);

    protected:

        xbutton_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using button_style = xmaterialize<xbutton_style>;

    using button_style_generator = xgenerator<xbutton_style>;

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void on_click(click_callback_type);

        XTRAIT(std::string, derived_type, description);

        XTRAIT(std::string, derived_type, tooltip);
        XTRAIT(bool, derived_type, disabled);
        XTRAIT(std::string, derived_type, icon);
        XTRAIT(std::string, derived_type, button_style, "", XEITHER("primary", "success", "info", "warning", "danger", ""));
        XTRAIT(::xw::button_style, derived_type, style);

        void handle_custom_message(const xeus::xjson&);

    protected:

        xbutton();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    using button = xmaterialize<xbutton>;

    using button_generator = xgenerator<xbutton>;

    /********************************
     * xbutton_style implementation *
     ********************************/

    template <class D>
    inline void xbutton_style<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(button_color, state, buffers);
        set_patch_from_property(font_weight, state, buffers);
    }

    template <class D>
    inline void xbutton_style<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(button_color, patch, buffers);
        set_property_from_patch(font_weight, patch, buffers);
    }

    template <class D>
    inline xbutton_style<D>::xbutton_style()
        : base_type()
    {
        set_defaults();
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
    inline void xbutton<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(description, state, buffers);
        set_patch_from_property(tooltip, state, buffers);
        set_patch_from_property(disabled, state, buffers);
        set_patch_from_property(icon, state, buffers);
        set_patch_from_property(button_style, state, buffers);
        set_patch_from_property(style, state, buffers);
    }

    template <class D>
    inline void xbutton<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description, patch, buffers);
        set_property_from_patch(tooltip, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(icon, patch, buffers);
        set_property_from_patch(button_style, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline void xbutton<D>::on_click(click_callback_type cb)
    {
        m_click_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    inline xbutton<D>::xbutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xbutton<D>::set_defaults()
    {
        this->_model_name() = "ButtonModel";
        this->_view_name() = "ButtonView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    template <class D>
    inline void xbutton<D>::handle_custom_message(const xeus::xjson& content)
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

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xbutton_style>;
    extern template xmaterialize<xbutton_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xbutton_style>>;
    extern template class xgenerator<xbutton_style>;
    extern template xgenerator<xbutton_style>::xgenerator();
    extern template class xtransport<xgenerator<xbutton_style>>;

    extern template class xmaterialize<xbutton>;
    extern template xmaterialize<xbutton>::xmaterialize();
    extern template class xtransport<xmaterialize<xbutton>>;
    extern template class xgenerator<xbutton>;
    extern template xgenerator<xbutton>::xgenerator();
    extern template class xtransport<xgenerator<xbutton>>;
#endif
}
#endif
