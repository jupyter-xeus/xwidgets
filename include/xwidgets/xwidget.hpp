#ifndef XWIDGET_HPP
#define XWIDGET_HPP

#include "xobject.hpp"

namespace xeus
{
    class xlayout final : public xobject<xlayout>
    {
    public:

        using base_type = xobject<xlayout>;

        xlayout();

        xjson get_state() const;

    private:

        void set_defaults();
    };

    template <class D>
    class xwidget : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xwidget();
    
        XPROPERTY(::xeus::xlayout, derived_type, layout);

        xjson get_state() const;

    private:

        void set_defaults();
    };

    /**************************
     * xlayout implementation *
     **************************/

    inline xlayout::xlayout()
        : base_type()
    {
        set_defaults();
        this->open();
    }

    inline xjson xlayout::get_state() const
    {
        xjson state = base_type::get_state();
        return state;
    }

    inline void xlayout::set_defaults()
    {
        base_type::_model_name.raw_value() = "LayoutModel";
        base_type::_view_name.raw_value() = "LayoutView";
    }

    /**************************
     * xwidget implementation *
     **************************/

    template <class D>
    inline xwidget<D>::xwidget()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xwidget<D>::get_state() const
    {
        xjson state = base_type::get_state();
        state["layout"] = xlayout();
        return state;
    }

    template <class D>
    inline void xwidget<D>::set_defaults()
    {
        base_type::_model_name() = "DOMWidgetModel";
        base_type::_view_name() = "DOMWidgetView";
        layout() = ::xeus::xlayout();
    }
}

#endif
