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

namespace xeus
{

    /****************************
     * base xnumber declaration *
     ****************************/

    template <class D> 
    struct xnumber_traits;

    template <class D>
    class xnumber : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        xnumber();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        using value_type = typename xnumber_traits<derived_type>::value_type;

        XPROPERTY(value_type, derived_type, value);
        XPROPERTY(value_type, derived_type, min);
        XPROPERTY(value_type, derived_type, max, value_type(100));

    private:

        void set_defaults();
    };

    /**************************
     * xnumber implementation *
     **************************/

    template <class D>
    inline xnumber<D>::xnumber()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xnumber<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);

        return state;
    }

    template <class D>
    inline void xnumber<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch)
    }

    template <class D>
    inline void xnumber<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "BoundedFloatModel";
        this->_view_name() = "BoundedFloatView";
    }
}

#endif
