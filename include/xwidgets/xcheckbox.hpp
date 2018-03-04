/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_CHECKBOX_HPP
#define XWIDGETS_CHECKBOX_HPP

#include "xboolean.hpp"
#include "xmaterialize.hpp"
#include "xprecompiled_macros.hpp"

namespace xw
{
    /************************
     * checkbox declaration *
     ************************/

    template <class D>
    class xcheckbox : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(bool, derived_type, indent, true);

    protected:

        xcheckbox();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using checkbox = xmaterialize<xcheckbox>;

    using checkbox_generator = xgenerator<xcheckbox>;

    /****************************
     * xcheckbox implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xcheckbox<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(indent, state);

        return state;
    }

    template <class D>
    inline void xcheckbox<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(indent, patch);
    }

    template <class D>
    inline xcheckbox<D>::xcheckbox()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcheckbox<D>::set_defaults()
    {
        this->_model_name() = "CheckboxModel";
        this->_view_name() = "CheckboxView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    XPRECOMPILE(EXTERN, (xcheckbox));
#endif
}

#endif
