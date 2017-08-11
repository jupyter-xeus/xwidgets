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

        XPROPERTY(double, xslider, value);

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

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);

        return state;
    }

    template <class T>
    inline void xslider<T>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
    }

    template <class T>
    inline void xslider<T>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "FloatSliderModel";
        this->_view_name() = "FloatSliderView";
    }
}

#endif
