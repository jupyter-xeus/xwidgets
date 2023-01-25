/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_SLIDER_HPP
#define XWIDGETS_SLIDER_HPP

#include <string>
#include <type_traits>

#include <xtl/xoptional.hpp>

#include "xcolor.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xnumber.hpp"
#include "xstyle.hpp"

namespace xw
{
    /****************************
     * slider_style declaration *
     ****************************/

    template <class D>
    class xslider_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<html_color>, derived_type, handle_color);

    protected:

        xslider_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using slider_style = xmaterialize<xslider_style>;

    /**********************
     * slider declaration *
     **********************/

    template <class D>
    class xslider : public xnumber<D>
    {
    public:

        using base_type = xnumber<D>;
        using derived_type = D;

        using value_type = typename base_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(
            std::string,
            derived_type,
            behavior,
            "drag-tap",
            XEITHER("drag-tap", "drag-snap", "tap", "drag", "snap")
        );
        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(bool, derived_type, readout, true);
        XPROPERTY(std::string, derived_type, readout_format, ".2f");
        XPROPERTY(::xw::slider_style, derived_type, style);

    protected:

        xslider();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T>
    using slider = xmaterialize<xslider, T>;

    template <class T>
    struct xnumber_traits<slider<T>>
    {
        using value_type = T;
    };

    /********************************
     * xslider_style implementation *
     ********************************/

    template <class D>
    inline void xslider_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description_width(), state["description_width"], buffers);
        xwidgets_serialize(handle_color(), state["handle_color"], buffers);
    }

    template <class D>
    inline void xslider_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(handle_color, patch, buffers);
    }

    template <class D>
    inline xslider_style<D>::xslider_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xslider_style<D>::set_defaults()
    {
        this->_model_name() = "SliderStyleModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /**************************
     * xslider implementation *
     **************************/

    template <class D>
    inline void xslider<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(behavior(), state["behavior"], buffers);
        xwidgets_serialize(orientation(), state["orientation"], buffers);
        xwidgets_serialize(readout(), state["readout"], buffers);
        xwidgets_serialize(readout_format(), state["readout_format"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xslider<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(behavior, patch, buffers);
        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(readout, patch, buffers);
        set_property_from_patch(readout_format, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xslider<D>::xslider()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xslider<D>::set_defaults()
    {
        // TODO(C++17) constexpr
        if (std::is_integral<value_type>::value)
        {
            this->_model_name() = "IntSliderModel";
            this->_view_name() = "IntSliderView";
        }
        else if (std::is_floating_point<value_type>::value)
        {
            this->_model_name() = "FloatSliderModel";
            this->_view_name() = "FloatSliderView";
        }
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xslider_style>;
    extern template class xtransport<xmaterialize<xslider_style>>;

    extern template class xmaterialize<xslider, int>;
    extern template class xtransport<xmaterialize<xslider, int>>;

    extern template class xmaterialize<xslider, float>;
    extern template class xtransport<xmaterialize<xslider, float>>;

    extern template class xmaterialize<xslider, double>;
    extern template class xtransport<xmaterialize<xslider, double>>;
}

#endif
