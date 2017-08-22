/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_SLIDER_HPP
#define XWIDGETS_SLIDER_HPP

#include "xnumber.hpp"
#include "xstyle.hpp"

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

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(XOPTIONAL(std::string), derived_type, handle_color);

    private:

        void set_defaults();
    };

    class slider_style final : public xslider_style<slider_style>
    {
    public:

        using base_type = xslider_style<slider_style>;

        slider_style()
            : base_type()
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

        slider_style(const slider_style& other)
            : base_type(other)
        {
            this->open();
        }

        slider_style& operator=(const slider_style& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }

        slider_style(slider_style&&) = default;
        slider_style& operator=(slider_style&&) = default;
    };

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

        xslider();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

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

        slider()
            : base_type()
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

        slider(const slider& other)
            : base_type(other)
        {
            this->open();
        }

        slider& operator=(const slider& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }

        slider(slider&&) = default;
        slider& operator=(slider&&) = default;
    };

    template <class T>
    struct xnumber_traits<slider<T>>
    {
        using value_type = T;
    };

    /********************************
     * xslider_style implementation *
     ********************************/

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

    /**************************
     * xslider implementation *
     **************************/

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
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";
    }
}

#endif
