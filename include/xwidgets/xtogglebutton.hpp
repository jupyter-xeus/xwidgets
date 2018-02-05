/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TOGGLE_HPP
#define XWIDGETS_TOGGLE_HPP

#include <string>

#include "xboolean.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"

namespace xw
{
    /****************************
     * togglebutton declaration *
     ****************************/

    template <class D>
    class xtogglebutton : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, tooltip);
        XPROPERTY(std::string, derived_type, icon);
        XPROPERTY(std::string, derived_type, button_style, "", XEITHER("primary", "success", "info", "warning", "danger", ""));

    protected:

        xtogglebutton();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebutton = xmaterialize<xtogglebutton>;

    using togglebutton_generator = xgenerator<xtogglebutton>;

    /********************************
     * xtogglebutton implementation *
     ********************************/

    template <class D>
    inline xtogglebutton<D>::xtogglebutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xeus::xjson xtogglebutton<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(icon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(button_style, state);

        return state;
    }

    template <class D>
    inline void xtogglebutton<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(icon, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_style, patch);
    }

    template <class D>
    inline void xtogglebutton<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonModel";
        this->_view_name() = "ToggleButtonView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xtogglebutton>;
    extern template xmaterialize<xtogglebutton>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebutton>>;
    extern template class xgenerator<xtogglebutton>;
    extern template xgenerator<xtogglebutton>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebutton>>;
}

#endif
