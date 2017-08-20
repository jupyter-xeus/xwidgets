/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_NUMBER_HPP
#define XWIDGETS_NUMBER_HPP

#include "xstyle.hpp"
#include "xwidget.hpp"

namespace xeus
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

        xslider_style();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(std::string), D, handle_color);

    private:

        void set_defaults();
    };

    class slider_style final : public xslider_style<slider_style>
    {
    public:

        using base_type = xslider_style<slider_style>;

        slider_style() : base_type()
        {
            this->open();
        }

        ~slider_style()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        slider_style(const slider_style& other) : base_type(other)
        {
            this->open();
        }

        slider_style& operator=(const slider_style& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /**********************
     * slider declaration *
     **********************/

    template <class D> 
    struct xslider_traits;

    template <class D>
    class xslider : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        xslider();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        using value_type = typename xslider_traits<derived_type>::value_type;

        // TODO value, min, max should be in a base numerical widget
        XPROPERTY(value_type, derived_type, value);
        XPROPERTY(value_type, derived_type, min);
        XPROPERTY(value_type, derived_type, max, value_type(100));

        XPROPERTY(value_type, derived_type, step, value_type(1));
        XPROPERTY(X_CASELESS_STR_ENUM(horizontal, vertical), derived_type, orientation, "horizontal");
        XPROPERTY(bool, derived_type, readout, true);
        XPROPERTY(std::string, derived_type, readout_format, ".2f");
        XPROPERTY(bool, derived_type, continuous_update, true);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(::xeus::slider_style, derived_type, style);

    private:

        void set_defaults();
    };

    template <class T>
    class slider final : public xslider<slider<T>>
    {
    public:

        using base_type = xslider<slider<T>>;

        slider() : base_type()
        {
            this->open();
        }

        ~slider()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        slider(const slider& other) : base_type(other)
        {
            this->open();
        }

        slider& operator=(const slider& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    template <class T> 
    struct xslider_traits<slider<T>>
    {
        using value_type = T;
    };

    /*******************************
     * slider_style implementation *
     *******************************/

    template <class D>
    inline xslider_style<D>::xslider_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xslider_style<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(handle_color, state);

        return state;
    }

    template <class D>
    inline void xslider_style<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(handle_color, patch);
    }

    template <class D>
    inline void xslider_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SliderStyleModel";
    }

    /*************************
     * slider implementation *
     *************************/

    template <class D>
    inline xslider<D>::xslider()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xslider<D>::get_state() const
    {
        xjson state = base_type::get_state();

        // TODO value, min, max should be in a base numerical widget
        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);

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
    inline void xslider<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        // TODO value, min, max should be in a base numerical widget
        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch)

        XOBJECT_SET_PROPERTY_FROM_PATCH(step, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(readout, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(readout_format, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch)
    }

    template <class D>
    inline void xslider<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";
    }
}

#endif
