/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_PASSWORD_HPP
#define XWIDGETS_PASSWORD_HPP

#include "xpassword.hpp"
#include "xstring.hpp"

namespace xeus
{
    /************************
     * password declaration *
     ************************/

    template <class D>
    class xpassword : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        xpassword();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(bool, derived_type, disabled);

    private:

        void set_defaults();
    };

    using password = xmaterialize<xpassword>;

    /****************************
     * xpassword implementation *
     ****************************/

    template <class D>
    inline xpassword<D>::xpassword()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xpassword<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);

        return state;
    }

    template <class D>
    inline void xpassword<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
    }

    template <class D>
    inline void xpassword<D>::set_defaults()
    {
        this->_model_name() = "PasswordModel";
        this->_view_name() = "PasswordView";
    }
}

#endif
