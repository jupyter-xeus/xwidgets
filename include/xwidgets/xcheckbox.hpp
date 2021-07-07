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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, indent, true);

    protected:

        xcheckbox();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using checkbox = xmaterialize<xcheckbox>;

    /****************************
     * xcheckbox implementation *
     ****************************/

    template <class D>
    inline void xcheckbox<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(indent(), state["indent"], buffers);
    }

    template <class D>
    inline void xcheckbox<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(indent, patch, buffers);
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

    extern template class xmaterialize<xcheckbox>;
    extern template class xtransport<xmaterialize<xcheckbox>>;
    extern template nl::json mime_bundle_repr<xcheckbox>(const xmaterialize<xcheckbox>&);
}

#endif
