/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_STRING_HPP
#define XWIDGETS_STRING_HPP

#include <string>

#include "xwidget.hpp"

namespace xw
{
    /****************************
     * base xstring declaration *
     ****************************/

    template <class D>
    class xstring : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        xstring();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(std::string, derived_type, value);
        XPROPERTY(std::string, derived_type, placeholder, "\u00A0");

    private:

        void set_defaults();
    };

    /**************************
     * xstring implementation *
     **************************/

    template <class D>
    inline xstring<D>::xstring()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xeus::xjson xstring<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(placeholder, state);

        return state;
    }

    template <class D>
    inline void xstring<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(placeholder, patch)
    }

    template <class D>
    inline void xstring<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "StringModel";
        this->_view_name() = "";
    }
}

#endif
