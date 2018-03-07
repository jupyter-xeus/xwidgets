/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_WIDGET_HPP
#define XWIDGETS_WIDGET_HPP

#include <string>
#include <vector>

#include "xlayout.hpp"
#include "xobject.hpp"

namespace xw
{
    /******************************
     * base xwidgets declarations *
     ******************************/

    template <class D>
    class xwidget : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(::xw::layout, derived_type, layout);
        XPROPERTY(std::vector<std::string>, derived_type, _dom_classes);

    protected:

        xwidget();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /********************************
     * base xwidgets implementation *
     ********************************/

    template <class D>
    inline xwidget<D>::xwidget()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xwidget<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(layout, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_dom_classes, patch);
    }

    template <class D>
    inline xeus::xjson xwidget<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(layout, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_dom_classes, state);

        return state;
    }

    template <class D>
    inline void xwidget<D>::set_defaults()
    {
        this->_model_name() = "DOMWidgetModel";
        this->_view_name() = "DOMWidgetView";
    }
}

#endif
