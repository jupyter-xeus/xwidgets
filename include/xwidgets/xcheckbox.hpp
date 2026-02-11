/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_CHECKBOX_HPP
#define XWIDGETS_CHECKBOX_HPP

#include <optional>
#include <string>

#include "xboolean.hpp"
#include "xmaterialize.hpp"
#include "xstyle.hpp"

namespace xw
{
    /********************************
     *  checkbox_style declaration  *
     ********************************/

    template <class D>
    class xcheckbox_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::optional<std::string>, xcommon, background);
        XPROPERTY(std::string, xcommon, description_width);

    protected:

        xcheckbox_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using checkbox_style = xmaterialize<xcheckbox_style>;

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

        XPROPERTY(bool, xcommon, indent, true);
        XPROPERTY(::xw::checkbox_style, xcommon, style);

    protected:

        xcheckbox();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using checkbox = xmaterialize<xcheckbox>;

    /************************************
     *  xcheckbox_style implementation  *
     ************************************/

    template <class D>
    inline void xcheckbox_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(background(), state["background"], buffers);
        xwidgets_serialize(description_width(), state["description_width"], buffers);
    }

    template <class D>
    inline void xcheckbox_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xcheckbox_style<D>::xcheckbox_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcheckbox_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "CheckboxStyleModel";
    }

    /****************************
     * xcheckbox implementation *
     ****************************/

    template <class D>
    inline void xcheckbox<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(indent(), state["indent"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xcheckbox<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
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

    extern template class xmaterialize<xcheckbox_style>;
    extern template class xtransport<xmaterialize<xcheckbox_style>>;

    extern template class xmaterialize<xcheckbox>;
    extern template class xtransport<xmaterialize<xcheckbox>>;
}

#endif
