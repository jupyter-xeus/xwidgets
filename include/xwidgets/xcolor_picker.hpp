/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_COLOR_PICKER_HPP
#define XWIDGETS_COLOR_PICKER_HPP

#include "xcolor.hpp"
#include "xmaterialize.hpp"
#include "xmixin_description.hpp"
#include "xwidget.hpp"

namespace xw
{
    /****************************
     * color_picker declaration *
     ****************************/

    template <class D>
    class xcolor_picker : public xwidget<D>,
                          public mixin::xdescription<D>
    {
    public:

        using derived_type = D;
        using base_type = xwidget<D>;
        using mixin_description_type = mixin::xdescription<D>;
        using value_type = html_color;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, concise);
        XPROPERTY(value_type, derived_type, value, "black");

    protected:

        xcolor_picker();

    private:

        void set_defaults();
    };

    using color_picker = xmaterialize<xcolor_picker>;

    /********************************
     * xcolor_picker implementation *
     ********************************/

    template <class D>
    inline void xcolor_picker<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
        mixin_description_type::serialize_state(state, buffers);

        xwidgets_serialize(concise(), state["concise"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(value(), state["value"], buffers);
    }

    template <class D>
    inline void xcolor_picker<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        mixin_description_type::apply_patch(patch, buffers);

        set_property_from_patch(concise, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline xcolor_picker<D>::xcolor_picker()
    {
        set_defaults();
    }

    template <class D>
    inline void xcolor_picker<D>::set_defaults()
    {
        this->_model_name() = "ColorPickerModel";
        this->_view_name() = "ColorPickerView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xcolor_picker>;
    extern template class xtransport<xmaterialize<xcolor_picker>>;
}

#endif
