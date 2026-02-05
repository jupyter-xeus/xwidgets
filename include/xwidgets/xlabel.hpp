/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_LABEL_HPP
#define XWIDGETS_LABEL_HPP

#include <optional>
#include <string>

#include "xmaterialize.hpp"
#include "xstring.hpp"
#include "xstyle.hpp"

namespace xw
{

    /*****************************
     *  label_style declaration  *
     *****************************/

    template <class D>
    class xlabel_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::optional<std::string>, xcommon, background);
        XPROPERTY(std::string, xcommon, description_width);
        XPROPERTY(std::optional<std::string>, xcommon, font_family);
        XPROPERTY(std::optional<std::string>, xcommon, font_size);
        XPROPERTY(std::optional<std::string>, xcommon, font_style);
        XPROPERTY(std::optional<std::string>, xcommon, font_variant);
        XPROPERTY(std::optional<std::string>, xcommon, font_weight);
        XPROPERTY(std::optional<std::string>, xcommon, text_color);
        XPROPERTY(std::optional<std::string>, xcommon, text_decoration);

    protected:

        xlabel_style();

    private:

        void set_defaults();
    };

    using label_style = xmaterialize<xlabel_style>;

    /*********************
     * label declaration *
     *********************/

    template <class D>
    class xlabel : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(::xw::label_style, xcommon, style);

    protected:

        xlabel();

    private:

        void set_defaults();
    };

    using label = xmaterialize<xlabel>;

    /*********************************
     *  xlabel_style implementation  *
     *********************************/

    template <class D>
    inline void xlabel_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(background(), state["background"], buffers);
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
    inline void xlabel_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(background, patch, buffers);
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
    inline xlabel_style<D>::xlabel_style()
    {
        set_defaults();
    }

    template <class D>
    inline void xlabel_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_model_name() = "LabelStyleModel";
    }

    /*************************
     * xlabel implementation *
     *************************/

    template <class D>
    inline void xlabel<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xlabel<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xlabel<D>::xlabel()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlabel<D>::set_defaults()
    {
        this->_model_name() = "LabelModel";
        this->_view_name() = "LabelView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xlabel>;
    extern template class xtransport<xmaterialize<xlabel>>;
}

#endif
