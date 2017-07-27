#ifndef XWIDGET_HPP
#define XWIDGET_HPP

#include "xobject.hpp"

namespace xeus
{
    class layout final : public xobject<layout>
    {
    public:

        using base_type = xobject<layout>;

        layout() : base_type()
        {
            set_defaults();
            this->open();
        }

        inline xjson get_state() const
        {
            xjson state = base_type::get_state();
            return state;
        }

    private:

        inline void set_defaults()
        {
            base_type::_model_name.raw_value() = "LayoutModel";
            base_type::_view_name.raw_value() = "LayoutView";
        }
    };

    template <class D>
    class xwidget : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xwidget() : base_type()
        {
            set_defaults();
        }
    
        XPROPERTY(::xeus::layout, derived_type, layout);

        inline xjson get_state() const
        {
            xjson state = base_type::get_state();
            state["layout"] = layout.raw_value();
            return state;
        }        

    private:

        inline void set_defaults()
        {
            base_type::_model_name.raw_value() = "DOMWidgetModel";
            base_type::_view_name.raw_value() = "DOMWidgetView";
            layout.raw_value() = ::xeus::layout();
        }
    };
}

#endif
