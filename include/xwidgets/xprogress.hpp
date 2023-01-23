/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_PROGRESS_HPP
#define XWIDGETS_PROGRESS_HPP

#include <string>
#include <type_traits>

#include "xcolor.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xnumber.hpp"
#include "xstyle.hpp"
#include "xtl/xoptional.hpp"

namespace xw
{
    /******************************
     * progress_style declaration *
     ******************************/

    template <class D>
    class xprogress_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<html_color>, derived_type, bar_color);

    protected:

        xprogress_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using progress_style = xmaterialize<xprogress_style>;

    /***********************
     * progress declaration *
     ***********************/

    template <class D>
    class xprogress : public xnumber<D>
    {
    public:

        using base_type = xnumber<D>;
        using derived_type = D;

        using value_type = typename base_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(std::string, derived_type, bar_style, "", XEITHER("success", "info", "warning", "danger", ""));
        XPROPERTY(::xw::progress_style, derived_type, style);

    protected:

        xprogress();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T>
    using progress = xmaterialize<xprogress, T>;

    template <class T>
    struct xnumber_traits<progress<T>>
    {
        using value_type = T;
    };

    /**********************************
     * xprogress_style implementation *
     **********************************/

    template <class D>
    inline void xprogress_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description_width(), state["description_width"], buffers);
        xwidgets_serialize(bar_color(), state["bar_color"], buffers);
    }

    template <class D>
    inline void xprogress_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(bar_color, patch, buffers);
    }

    template <class D>
    inline xprogress_style<D>::xprogress_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xprogress_style<D>::set_defaults()
    {
        this->_model_name() = "ProgressStyleModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /****************************
     * xprogress implementation *
     ****************************/

    template <class D>
    inline void xprogress<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(orientation(), state["orientation"], buffers);
        xwidgets_serialize(bar_style(), state["bar_style"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xprogress<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(bar_style, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xprogress<D>::xprogress()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xprogress<D>::set_defaults()
    {
        // TODO(C++17) constexpr
        if (std::is_integral<value_type>::value)
        {
            this->_model_name() = "IntProgressModel";
        }
        else if (std::is_floating_point<value_type>::value)
        {
            this->_model_name() = "FloatProgressModel";
        }
        this->_view_name() = "ProgressView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xprogress_style>;
    extern template class xtransport<xmaterialize<xprogress_style>>;

    extern template class xmaterialize<xprogress, int>;
    extern template class xtransport<xmaterialize<xprogress, int>>;

    extern template class xmaterialize<xprogress, float>;
    extern template class xtransport<xmaterialize<xprogress, float>>;

    extern template class xmaterialize<xprogress, double>;
    extern template class xtransport<xmaterialize<xprogress, double>>;
}

#endif
