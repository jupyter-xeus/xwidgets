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

#include <xtl/xoptional.hpp>

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<html_color>, derived_type, button_color);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_family);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_size);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_style);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_variant);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_weight);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, text_color);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, text_decoration);

    protected:

        xbutton_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using button_style = xmaterialize<xbutton_style>;

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_click(click_callback_type);

        XPROPERTY(std::string, derived_type, description);

        XPROPERTY(std::string, derived_type, tooltip);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(std::string, derived_type, icon);
        XPROPERTY(
            std::string,
            derived_type,
            button_style,
            "",
            XEITHER("primary", "success", "info", "warning", "danger", "")
        );
        XPROPERTY(::xw::button_style, derived_type, style);

        void handle_custom_message(const nl::json&);

    protected:

        xbutton();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    using button = xmaterialize<xbutton>;

    /********************************
     * xbutton_style implementation *
     ********************************/

    template <class D>
    inline void xbutton_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(button_color(), state["button_color"], buffers);
        xwidgets_serialize(font_family(), state["font_family"], buffers);
        xwidgets_serialize(font_size(), state["font_size"], buffers);
        xwidgets_serialize(font_style(), state["font_style"], buffers);
        xwidgets_serialize(font_variant(), state["font_variant"], buffers);
        xwidgets_serialize(font_weight(), state["font_weight"], buffers);
        xwidgets_serialize(text_color(), state["text_color"], buffers);
        xwidgets_serialize(text_decoration(), state["text_decoration"], buffers);
    }

    template <class D>
    inline void xbutton_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(button_color, patch, buffers);
        set_property_from_patch(font_family, patch, buffers);
        set_property_from_patch(font_size, patch, buffers);
        set_property_from_patch(font_style, patch, buffers);
        set_property_from_patch(font_variant, patch, buffers);
        set_property_from_patch(font_weight, patch, buffers);
        set_property_from_patch(text_color, patch, buffers);
        set_property_from_patch(text_decoration, patch, buffers);
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
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_model_name() = "ButtonStyleModel";
    }

    /**************************
     * xbutton implementation *
     **************************/

    template <class D>
    inline void xbutton<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description(), state["description"], buffers);
        xwidgets_serialize(tooltip(), state["tooltip"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(icon(), state["icon"], buffers);
        xwidgets_serialize(button_style(), state["button_style"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xbutton<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
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
    inline void xbutton<D>::handle_custom_message(const nl::json& content)
    {
        auto const event_it = content.find("event");
        if (event_it != content.end() && event_it.value() == "click")
        {
            for (auto& callback : m_click_callbacks)
            {
                callback();
            }
        }
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xbutton_style>;
    extern template class xtransport<xmaterialize<xbutton_style>>;

    extern template class xmaterialize<xbutton>;
    extern template class xtransport<xmaterialize<xbutton>>;
}
#endif
