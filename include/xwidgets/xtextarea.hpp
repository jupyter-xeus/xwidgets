/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_TEXTAREA_HPP
#define XWIDGETS_TEXTAREA_HPP

#include <optional>

#include "xmaterialize.hpp"
#include "xstring.hpp"
#include "xtext.hpp"

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

        XPROPERTY(std::optional<int>, xcommon, rows);
        XPROPERTY(bool, xcommon, disabled);
        XPROPERTY(bool, xcommon, continuous_update, true);
        XPROPERTY(::xw::text_style, xcommon, style);

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
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xtextarea<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xtextarea<D>::xtextarea()
        : base_type()
    {
        set_defaults();
        REGISTER_PROPERTIES(rows, disabled, continuous_update, style);
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
}

#endif
