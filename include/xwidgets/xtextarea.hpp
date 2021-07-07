/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TEXTAREA_HPP
#define XWIDGETS_TEXTAREA_HPP

#include "xmaterialize.hpp"
#include "xstring.hpp"

namespace xw
{
    /************************
     * textarea declaration *
     ************************/

    template <class D>
    class xtextarea : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<int>, derived_type, rows);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update, true);

    protected:

        xtextarea();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using textarea = xmaterialize<xtextarea>;

    /****************************
     * xtextarea implementation *
     ****************************/

    template <class D>
    inline void xtextarea<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(rows(), state["rows"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
    }

    template <class D>
    inline void xtextarea<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(rows, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
    }

    template <class D>
    inline xtextarea<D>::xtextarea()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtextarea<D>::set_defaults()
    {
        this->_model_name() = "TextareaModel";
        this->_view_name() = "TextareaView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xtextarea>;
    extern template class xtransport<xmaterialize<xtextarea>>;
    extern template nl::json mime_bundle_repr<xtextarea>(const xmaterialize<xtextarea>&);
}

#endif
