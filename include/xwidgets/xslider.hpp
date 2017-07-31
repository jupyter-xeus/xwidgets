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
        void set_state(const xjson& state);

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
        state["value"] = value();
        return state;
    }

    template <class T>
    inline void xslider<T>::set_state(const xjson& state)
    {
        if (state.find("value") != state.end())
            value = state.at("value").get<double>();
    }

    template <class T>
    inline void xslider<T>::set_defaults()
    {
        base_type::_model_name() = "FloatSliderModel";
        base_type::_view_name() = "FloatSliderView";
    }
}

#endif
