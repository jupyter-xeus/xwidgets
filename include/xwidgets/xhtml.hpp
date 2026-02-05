/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_HTML_HPP
#define XWIDGETS_HTML_HPP

#include <optional>
#include <string>

#include "xmaterialize.hpp"
#include "xstring.hpp"
#include "xstyle.hpp"

namespace xw
{
    /****************************
     * html_style declaration *
     ****************************/

    template <class D>
    class xhtml_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::optional<std::string>, xcommon, background);
        XPROPERTY(std::string, xcommon, description_width);
        XPROPERTY(std::optional<std::string>, xcommon, font_size);
        XPROPERTY(std::optional<std::string>, xcommon, text_color);

    protected:

        xhtml_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using html_style = xmaterialize<xhtml_style>;

    /********************
     * html declaration *
     ********************/

    template <class D>
    class xhtml : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(::xw::html_style, xcommon, style);

    protected:

        xhtml();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using html = xmaterialize<xhtml>;

    /********************************
     * xhtml_style implementation *
     ********************************/

    template <class D>
    inline void xhtml_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(background(), state["background"], buffers);
        xwidgets_serialize(description_width(), state["description_width"], buffers);
        xwidgets_serialize(font_size(), state["font_size"], buffers);
        xwidgets_serialize(text_color(), state["text_color"], buffers);
    }

    template <class D>
    inline void xhtml_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(background, patch, buffers);
        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(font_size, patch, buffers);
        set_property_from_patch(text_color, patch, buffers);
    }

    template <class D>
    inline xhtml_style<D>::xhtml_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xhtml_style<D>::set_defaults()
    {
        this->_model_name() = "HTMLStyleModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /************************
     * xhtml implementation *
     ************************/

    template <class D>
    inline void xhtml<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xhtml<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xhtml<D>::xhtml()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xhtml<D>::set_defaults()
    {
        this->_model_name() = "HTMLModel";
        this->_view_name() = "HTMLView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xhtml_style>;
    extern template class xtransport<xmaterialize<xhtml_style>>;

    extern template class xmaterialize<xhtml>;
    extern template class xtransport<xmaterialize<xhtml>>;
}

#endif
