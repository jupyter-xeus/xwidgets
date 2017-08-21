/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BOOLEAN_HPP
#define XWIDGETS_BOOLEAN_HPP

#include "xwidget.hpp"

namespace xeus
{

    /*****************************
     * base xboolean declaration *
     *****************************/

    template <class D>
    class xboolean : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        xboolean();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(std::string, derived_type, description);

        XPROPERTY(bool, derived_type, value);
        XPROPERTY(bool, derived_type, disabled);

    private:

        void set_defaults();
    };

    /***************************
     * xboolean implementation *
     ***************************/

    template <class D>
    inline xboolean<D>::xboolean()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xboolean<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);

        return state;
    }

    template <class D>
    inline void xboolean<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
    }

    template <class D>
    inline void xboolean<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "BoolModel";
    }
}

#endif
