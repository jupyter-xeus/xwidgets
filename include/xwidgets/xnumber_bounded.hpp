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

#include "xmaterialize.hpp"
#include "xmixin_description.hpp"
#include "xmixin_numeric.hpp"
#include "xwidget.hpp"

namespace xw
{
    /*********************************
     *  xnumber_bounded declaration  *
     *********************************/

    template <class D>
    class xnumber_bounded : public xwidget<D>,
                            public mixin::xdescription<D>,
                            public mixin::xnumeric_bounded<D>
    {
    public:

        using derived_type = D;
        using base_type = xwidget<D>;
        using mixin_description_type = mixin::xdescription<D>;
        using mixin_numeric_type = mixin::xnumeric_bounded<D>;
        using typename mixin_numeric_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, xcommon, continuous_update);
        XPROPERTY(bool, xcommon, disabled);
        XPROPERTY(value_type, xcommon, step);

    protected:

        xnumber_bounded();

    private:

        void set_defaults();
    };

    template <class T>
    using number_bounded = xmaterialize<xnumber_bounded, T>;

    template <class T>
    struct xnumber_traits<number_bounded<T>>
    {
        using value_type = T;
    };

    /**************************
     * xnumber implementation *
     **************************/

    template <class D>
    inline void xnumber_bounded<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
        mixin_description_type::serialize_state(state, buffers);
        mixin_numeric_type::serialize_state(state, buffers);

        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(step(), state["step"], buffers);
    }

    template <class D>
    inline void xnumber_bounded<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xnumber_bounded<D>::xnumber_bounded()
    {
        set_defaults();
    }

    template <class D>
    inline void xnumber_bounded<D>::set_defaults()
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
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module() = "@jupyter-widgets/controls";
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xnumber_bounded, int>;
    extern template class xtransport<xmaterialize<xnumber_bounded, int>>;

    extern template class xmaterialize<xnumber_bounded, float>;
    extern template class xtransport<xmaterialize<xnumber_bounded, float>>;

    extern template class xmaterialize<xnumber_bounded, double>;
    extern template class xtransport<xmaterialize<xnumber_bounded, double>>;
}

#endif
