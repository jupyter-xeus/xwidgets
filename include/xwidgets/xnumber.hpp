/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_NUMBER_HPP
#define XWIDGETS_NUMBER_HPP

#include <type_traits>

#include "xnumeral.hpp"
#include "xwidget.hpp"

namespace xw
{
    /***********************
     * xnumber declaration *
     ***********************/

    template <class D>
    class xnumber : public xnumeral<D>
    {
    public:

        using base_type = xnumeral<D>;
        using derived_type = D;
        using value_type = typename base_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, max, value_type(100));
        XPROPERTY(value_type, derived_type, min);

    protected:

        xnumber();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T>
    using number = xmaterialize<xnumber, T>;

    template <class T>
    struct xnumber_traits<number<T>>
    {
        using value_type = T;
    };

    /**************************
     * xnumber implementation *
     **************************/

    template <class D>
    inline void xnumber<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(max(), state["max"], buffers);
        xwidgets_serialize(min(), state["min"], buffers);
    }

    template <class D>
    inline void xnumber<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(min, patch, buffers);
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
        // TODO(C++17) constexpr
        if (std::is_integral<value_type>::value)
        {
            this->_model_name() = "BoundedIntTextModel";
            this->_view_name() = "IntTextView";
        }
        else if (std::is_floating_point<value_type>::value)
        {
            this->_model_name() = "BoundedFloatTextModel";
            this->_view_name() = "FloatTextView";
        }
        else
        {
            return;
        }
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xnumber, int>;
    extern template class xtransport<xmaterialize<xnumber, int>>;

    extern template class xmaterialize<xnumber, float>;
    extern template class xtransport<xmaterialize<xnumber, float>>;

    extern template class xmaterialize<xnumber, double>;
    extern template class xtransport<xmaterialize<xnumber, double>>;
}

#endif
