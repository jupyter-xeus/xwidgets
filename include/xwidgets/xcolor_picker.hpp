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
#include "xwidget.hpp"

namespace xw
{
    /****************************
     * color_picker declaration *
     ****************************/

    template <class D>
    class xcolor_picker : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        using value_type = html_color;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, value, "black");
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, concise);

    protected:

        xcolor_picker();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using color_picker = xmaterialize<xcolor_picker>;

    using color_picker_generator = xgenerator<xcolor_picker>;

    /********************************
     * xcolor_picker implementation *
     ********************************/

    template <class D>
    inline void xcolor_picker<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(value, state, buffers);
        this->set_patch_from_property(disabled, state, buffers);
        this->set_patch_from_property(value, state, buffers);
    }

    template <class D>
    inline void xcolor_picker<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(value, patch, buffers);
        this->set_property_from_patch(disabled, patch, buffers);
        this->set_property_from_patch(concise, patch, buffers);
    }

    template <class D>
    inline xcolor_picker<D>::xcolor_picker()
        : base_type()
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

#ifndef _WIN32
    extern template class xmaterialize<xcolor_picker>;
    extern template xmaterialize<xcolor_picker>::xmaterialize();
    extern template class xtransport<xmaterialize<xcolor_picker>>;
    extern template class xgenerator<xcolor_picker>;
    extern template xgenerator<xcolor_picker>::xgenerator();
    extern template class xtransport<xgenerator<xcolor_picker>>;
#endif 
}

#endif
