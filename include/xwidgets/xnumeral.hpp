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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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
    struct xnumber_traits<numeral<T>>
    {
        using value_type = T;
    };

    /***************************
     * xnumeral implementation *
     ***************************/

    template <class D>
    inline void xnumeral<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(step(), state["step"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
    }

    template <class D>
    inline void xnumeral<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(step, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
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

    extern template class xmaterialize<xnumeral, int>;
    extern template class xtransport<xmaterialize<xnumeral, int>>;
    extern template nl::json mime_bundle_repr<xnumeral, int>(const xmaterialize<xnumeral, int>&);

    extern template class xmaterialize<xnumeral, float>;
    extern template class xtransport<xmaterialize<xnumeral, float>>;
    extern template nl::json mime_bundle_repr<xnumeral, float>(const xmaterialize<xnumeral, float>&);

    extern template class xmaterialize<xnumeral, double>;
    extern template class xtransport<xmaterialize<xnumeral, double>>;
    extern template nl::json mime_bundle_repr<xnumeral, double>(const xmaterialize<xnumeral, double>&);
}

#endif
