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

namespace xw
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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, disabled);

    protected:

        xpassword();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using password = xmaterialize<xpassword>;

    /****************************
     * xpassword implementation *
     ****************************/

    template <class D>
    inline void xpassword<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(disabled(), state["disabled"], buffers);
    }

    template <class D>
    inline void xpassword<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(disabled, patch, buffers);
    }

    template <class D>
    inline xpassword<D>::xpassword()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpassword<D>::set_defaults()
    {
        this->_model_name() = "PasswordModel";
        this->_view_name() = "PasswordView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xpassword>;
    extern template class xtransport<xmaterialize<xpassword>>;
}

#endif
