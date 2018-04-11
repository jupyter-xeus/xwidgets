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

#include "xtl/xoptional.hpp"

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<html_color>, derived_type, handle_color);

    protected:

        xslider_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using slider_style = xmaterialize<xslider_style>;

    using slider_style_generator = xgenerator<xslider_style>;

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, step, value_type(1));
        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(bool, derived_type, readout, true);
        XPROPERTY(std::string, derived_type, readout_format, ".2f");
        XPROPERTY(bool, derived_type, continuous_update, true);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(::xw::slider_style, derived_type, style);

    protected:

        xslider();
        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    template <class T>
    using slider = xmaterialize<xslider, T>;

    template <class T>
    using slider_generator = xgenerator<xslider, T>;

    template <class T>
    struct xnumber_traits<slider<T>>
    {
        using value_type = T;
    };

    template <class T>
    struct xnumber_traits<slider_generator<T>>
    {
        using value_type = T;
    };

    /********************************
     * xslider_style implementation *
     ********************************/

    template <class D>
    inline void xslider_style<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(description_width, state, buffers);
        set_patch_from_property(handle_color, state, buffers);
    }

    template <class D>
    inline void xslider_style<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
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
    inline void xslider<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(step, state, buffers);
        set_patch_from_property(orientation, state, buffers);
        set_patch_from_property(readout, state, buffers);
        set_patch_from_property(readout_format, state, buffers);
        set_patch_from_property(continuous_update, state, buffers);
        set_patch_from_property(disabled, state, buffers);
        set_patch_from_property(style, state, buffers);
    }

    template <class D>
    inline void xslider<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(step, patch, buffers);
        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(readout, patch, buffers);
        set_property_from_patch(readout_format, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xslider<D>::xslider()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    inline void xslider<D>::setup_properties()
    {
        auto self = this->self();
        self->template validate<decltype(self->value)>([](auto& owner, auto& proposal) {
            if (proposal > owner.max())
            {
                proposal = owner.max();
            }
            if (proposal < owner.min())
            {
                proposal = owner.min();
            }
        });

        self->template validate<decltype(self->min)>([](auto& owner, auto& proposal) {
            if (proposal > owner.max())
            {
                throw std::runtime_error("setting min > max");
            }
            if (proposal > owner.value())
            {
                owner.value = proposal;
            }
        });

        self->template validate<decltype(self->max)>([](auto& owner, auto& proposal) {
            if (proposal < owner.min())
            {
                throw std::runtime_error("setting max < min");
            }
            if (proposal < owner.value())
            {
                owner.value = proposal;
            }
        });
    }

    template <class D>
    inline void xslider<D>::set_defaults()
    {
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xslider_style>;
    extern template xmaterialize<xslider_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider_style>>;
    extern template class xgenerator<xslider_style>;
    extern template xgenerator<xslider_style>::xgenerator();
    extern template class xtransport<xgenerator<xslider_style>>;

    extern template class xmaterialize<xslider, int>;
    extern template xmaterialize<xslider, int>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, int>>;
    extern template class xgenerator<xslider, int>;
    extern template xgenerator<xslider, int>::xgenerator();
    extern template class xtransport<xgenerator<xslider, int>>;

    extern template class xmaterialize<xslider, float>;
    extern template xmaterialize<xslider, float>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, float>>;
    extern template class xgenerator<xslider, float>;
    extern template xgenerator<xslider, float>::xgenerator();
    extern template class xtransport<xgenerator<xslider, float>>;

    extern template class xmaterialize<xslider, double>;
    extern template xmaterialize<xslider, double>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, double>>;
    extern template class xgenerator<xslider, double>;
    extern template xgenerator<xslider, double>::xgenerator();
    extern template class xtransport<xgenerator<xslider, double>>;
#endif
}

#endif
