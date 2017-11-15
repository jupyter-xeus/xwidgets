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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, handle_color);

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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
    inline xeus::xjson xslider_style<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(description_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(handle_color, state);

        return state;
    }

    template <class D>
    inline void xslider_style<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(description_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(handle_color, patch);
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SliderStyleModel";
    }

    /**************************
     * xslider implementation *
     **************************/

    template <class D>
    inline xeus::xjson xslider<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(step, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(readout, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(readout_format, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    template <class D>
    inline void xslider<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(step, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(readout, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(readout_format, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch)
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
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";
    }
}

#endif
