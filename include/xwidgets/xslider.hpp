#ifndef XSLIDER_HPP
#define XSLIDER_HPP

#include "xwidget.hpp"

namespace xeus
{
    template <class T>
    class slider final : public xwidget<slider<T>>
    {
    public:

        using base_type = xwidget<slider<T>>;

        slider() : base_type()
        {
            set_defaults();
            this->open();
        }

        XPROPERTY(double, slider, value);

        inline xjson get_state() const
        {
            xjson state = base_type::get_state();
            state["value"] = value.raw_value();
            return state;
        }

        inline void set_state(const xjson& state)
        {
            if (state.find("value") != state.end())
                value = state.at("value").get<double>();
            //p.address = j.at("address").get<std::string>();
            //p.age = j.at("age").get<int>();   
        }

    private:

        inline void set_defaults()
        {
            base_type::_model_name.raw_value() = "FloatSliderModel";
            base_type::_view_name.raw_value() = "FloatSliderView";
        }
    };
}

#endif
