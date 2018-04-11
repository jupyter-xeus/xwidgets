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

namespace xw
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(value_type, derived_type, step);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update);

    protected:

        xnumeral();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T>
    using numeral = xmaterialize<xnumeral, T>;

    template <class T>
    using numeral_generator = xgenerator<xnumeral, T>;

    template <class T>
    struct xnumber_traits<numeral<T>>
    {
        using value_type = T;
    };

    template <class T>
    struct xnumber_traits<numeral_generator<T>>
    {
        using value_type = T;
    };

    /***************************
     * xnumeral implementation *
     ***************************/

    template <class D>
    inline xeus::xjson xnumeral<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(step, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xnumeral<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(step, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch);
    }

    template <class D>
    inline xnumeral<D>::xnumeral()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xnumeral<D>::set_defaults()
    {
        this->_model_name() = "FloatTextModel";
        this->_view_name() = "FloatTextView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xnumeral, int>;
    extern template xmaterialize<xnumeral, int>::xmaterialize();
    extern template class xtransport<xmaterialize<xnumeral, int>>;
    extern template class xgenerator<xnumeral, int>;
    extern template xgenerator<xnumeral, int>::xgenerator();
    extern template class xtransport<xgenerator<xnumeral, int>>;

    extern template class xmaterialize<xnumeral, float>;
    extern template xmaterialize<xnumeral, float>::xmaterialize();
    extern template class xtransport<xmaterialize<xnumeral, float>>;
    extern template class xgenerator<xnumeral, float>;
    extern template xgenerator<xnumeral, float>::xgenerator();
    extern template class xtransport<xgenerator<xnumeral, float>>;

    extern template class xmaterialize<xnumeral, double>;
    extern template xmaterialize<xnumeral, double>::xmaterialize();
    extern template class xtransport<xmaterialize<xnumeral, double>>;
    extern template class xgenerator<xnumeral, double>;
    extern template xgenerator<xnumeral, double>::xgenerator();
    extern template class xtransport<xgenerator<xnumeral, double>>;
#endif
}

#endif
