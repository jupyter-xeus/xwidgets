/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_NUMBER_HPP
#define XWIDGETS_NUMBER_HPP

#include "xwidget.hpp"

namespace xw
{
    /***********************
     * xnumber declaration *
     ***********************/

    template <class D>
    struct xnumber_traits;

    template <class D>
    class xnumber : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        using value_type = typename xnumber_traits<derived_type>::value_type;

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(bool, derived_type, description_allow_html, false);
        XPROPERTY(value_type, derived_type, max, value_type(100));
        XPROPERTY(value_type, derived_type, min);
        XPROPERTY(value_type, derived_type, value);

    protected:

        xnumber();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /**************************
     * xnumber implementation *
     **************************/

    template <class D>
    inline void xnumber<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description(), state["description"], buffers);
        xwidgets_serialize(description_allow_html(), state["description_allow_html"], buffers);
        xwidgets_serialize(max(), state["max"], buffers);
        xwidgets_serialize(min(), state["min"], buffers);
        xwidgets_serialize(value(), state["value"], buffers);
    }

    template <class D>
    inline void xnumber<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description, patch, buffers);
        set_property_from_patch(description_allow_html, patch, buffers);
        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(min, patch, buffers);
        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline xnumber<D>::xnumber()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xnumber<D>::set_defaults()
    {
        this->_model_name() = "BoundedFloatModel";
        this->_view_name() = "BoundedFloatView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }
}

#endif
