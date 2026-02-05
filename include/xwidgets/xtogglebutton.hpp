/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_TOGGLE_HPP
#define XWIDGETS_TOGGLE_HPP

#include <optional>
#include <string>

#include "xboolean.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xstyle.hpp"

namespace xw
{
    /********************************
     *  togglebutton_style declaration  *
     ********************************/

    template <class D>
    class xtogglebutton_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, xcommon, description_width);
        XPROPERTY(std::optional<std::string>, xcommon, font_family);
        XPROPERTY(std::optional<std::string>, xcommon, font_size);
        XPROPERTY(std::optional<std::string>, xcommon, font_style);
        XPROPERTY(std::optional<std::string>, xcommon, font_variant);
        XPROPERTY(std::optional<std::string>, xcommon, font_weight);
        XPROPERTY(std::optional<std::string>, xcommon, text_color);
        XPROPERTY(std::optional<std::string>, xcommon, text_decoration);

    protected:

        xtogglebutton_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebutton_style = xmaterialize<xtogglebutton_style>;

    /****************************
     * togglebutton declaration *
     ****************************/

    template <class D>
    class xtogglebutton : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, xcommon, tooltip);
        XPROPERTY(std::string, xcommon, icon);
        XPROPERTY(
            std::string,
            xcommon,
            button_style,
            "",
            XEITHER("primary", "success", "info", "warning", "danger", "")
        );
        XPROPERTY(::xw::togglebutton_style, xcommon, style);

    protected:

        xtogglebutton();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebutton = xmaterialize<xtogglebutton>;

    /***********************************
     *  togglebutton_style implementation  *
     ***********************************/

    template <class D>
    inline void xtogglebutton_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description_width(), state["description_width"], buffers);
        xwidgets_serialize(font_family(), state["font_family"], buffers);
        xwidgets_serialize(font_size(), state["font_size"], buffers);
        xwidgets_serialize(font_style(), state["font_style"], buffers);
        xwidgets_serialize(font_variant(), state["font_variant"], buffers);
        xwidgets_serialize(font_weight(), state["font_weight"], buffers);
        xwidgets_serialize(text_color(), state["text_color"], buffers);
        xwidgets_serialize(text_decoration(), state["text_decoration"], buffers);
    }

    template <class D>
    inline void xtogglebutton_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(font_family, patch, buffers);
        set_property_from_patch(font_size, patch, buffers);
        set_property_from_patch(font_style, patch, buffers);
        set_property_from_patch(font_variant, patch, buffers);
        set_property_from_patch(font_weight, patch, buffers);
        set_property_from_patch(text_color, patch, buffers);
        set_property_from_patch(text_decoration, patch, buffers);
    }

    template <class D>
    inline xtogglebutton_style<D>::xtogglebutton_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtogglebutton_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ToggleButtonStyleModel";
    }

    /********************************
     * xtogglebutton implementation *
     ********************************/

    template <class D>
    inline xtogglebutton<D>::xtogglebutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtogglebutton<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(tooltip(), state["tooltip"], buffers);
        xwidgets_serialize(icon(), state["icon"], buffers);
        xwidgets_serialize(button_style(), state["button_style"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xtogglebutton<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(tooltip, patch, buffers);
        set_property_from_patch(icon, patch, buffers);
        set_property_from_patch(button_style, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline void xtogglebutton<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonModel";
        this->_view_name() = "ToggleButtonView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xtogglebutton>;
    extern template class xtransport<xmaterialize<xtogglebutton>>;

    extern template class xmaterialize<xtogglebutton_style>;
    extern template class xtransport<xmaterialize<xtogglebutton_style>>;

}

#endif
