/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_NUMERAL_HPP
#define XWIDGETS_NUMERAL_HPP

#include "xmaterialize.hpp"
#include "xnumber.hpp"

namespace xeus
{
    /***********************
     * numeral declaration *
     ***********************/

    template <class D>
    class xnumeral : public xnumber<D>
    {
    public:

        using base_type = xnumber<D>;
        using derived_type = D;
        using value_type = typename base_type::value_type;

        xnumeral();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(value_type, derived_type, step);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update);

    private:

        void set_defaults();
    };

    template <class T>
    using numeral = xmaterialize<xnumeral, T>;

    template <class T>
    struct xnumber_traits<numeral<T>>
    {
        using value_type = T;
    };

    /***************************
     * xnumeral implementation *
     ***************************/

    template <class D>
    inline xnumeral<D>::xnumeral()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xnumeral<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(step, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xnumeral<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(step, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
    }

    template <class D>
    inline void xnumeral<D>::set_defaults()
    {
        this->_model_name() = "FloatTextModel";
        this->_view_name() = "FloatTextView";
    }
}

#endif
