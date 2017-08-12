#ifndef XSLIDER_HPP
#define XSLIDER_HPP

#include "xwidget.hpp"

namespace xeus
{
    template <class T>
    class xslider final : public xwidget<xslider<T>>
    {
    public:

        using base_type = xwidget<xslider<T>>;

        xslider();

        // TODO value, min, max should be in a base numerical widget
        XPROPERTY(T, xslider, value);
        XPROPERTY(T, xslider, min);
        XPROPERTY(T, xslider, max);

        XPROPERTY(T, xslider, step);
        XPROPERTY(X_CASELESS_STR_ENUM(horizontal, vertical), xslider, orientation);
        XPROPERTY(bool, xslider, readout);
        XPROPERTY(std::string, xslider, readout_format);
        XPROPERTY(bool, xslider, continuous_update);
        XPROPERTY(bool, xslider, disabled);
        // XPROPERTY(xslider_style, xslider, style);

        xjson get_state() const;
        void apply_patch(const xjson& patch);

    private:

        void set_defaults();
    };

    /**************************
     * xslider implementation *
     **************************/

    template <class T>
    inline xslider<T>::xslider()
        : base_type()
    {
        set_defaults();
        this->open();
    }

    template <class T>
    inline xjson xslider<T>::get_state() const
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
        // XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    template <class T>
    inline void xslider<T>::apply_patch(const xjson& patch)
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
        // XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch)
    }

    template <class T>
    inline void xslider<T>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";

        this->max() = T(100);
        this->step() = T(1);

        // TODO: use a macro for xproperty defaults when they differ from default constructed
        this->orientation() = "horizontal";
        this->readout() = true;
        this->readout_format() = ".2f";
        this->continuous_update() = true;
    }
}

#endif
