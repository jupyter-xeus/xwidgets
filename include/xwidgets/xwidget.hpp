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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xwidget<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(layout, patch, buffers);
        set_property_from_patch(_dom_classes, patch, buffers);
    }

    template <class D>
    inline void xwidget<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(layout, state, buffers);
        set_patch_from_property(_dom_classes, state, buffers);
    }

    template <class D>
    inline void xwidget<D>::set_defaults()
    {
        this->_model_name() = "DOMWidgetModel";
        this->_view_name() = "DOMWidgetView";
    }
}

#endif
