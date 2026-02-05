/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_PLAY_HPP
#define XWIDGETS_PLAY_HPP

#include "xmaterialize.hpp"
#include "xmixin_description.hpp"
#include "xmixin_numeric.hpp"
#include "xwidget.hpp"

namespace xw
{
    /********************
     * play declaration *
     ********************/

    template <class D>
    class xplay : public xwidget<D>,
                  public mixin::xdescription<D>,
                  public mixin::xnumeric_bounded<D>
    {
    public:

        using derived_type = D;
        using base_type = xwidget<D>;
        using mixin_description_type = mixin::xdescription<D>;
        using mixin_numeric_type = mixin::xnumeric_bounded<D>;
        using typename mixin_numeric_type::value_type;

        void serialize_state(nl::json& state, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, xcommon, disabled);
        XPROPERTY(value_type, xcommon, interval, value_type(100));
        XPROPERTY(bool, xcommon, playing);
        XPROPERTY(bool, xcommon, repeat);
        XPROPERTY(bool, xcommon, show_repeat, true);
        XPROPERTY(value_type, xcommon, step, value_type(1));

    protected:

        xplay();

    private:

        void set_defaults();
    };

    using play = xmaterialize<xplay>;

    template <>
    struct xnumber_traits<play>
    {
        using value_type = int;
    };

    /************************
     * xplay implementation *
     ************************/

    template <class D>
    inline void xplay<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
        mixin_description_type::serialize_state(state, buffers);
        mixin_numeric_type::serialize_state(state, buffers);

        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(interval(), state["interval"], buffers);
        xwidgets_serialize(playing(), state["playing"], buffers);
        xwidgets_serialize(repeat(), state["repeat"], buffers);
        xwidgets_serialize(show_repeat(), state["show_repeat"], buffers);
        xwidgets_serialize(step(), state["step"], buffers);
    }

    template <class D>
    inline void xplay<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        mixin_description_type::apply_patch(patch, buffers);
        mixin_numeric_type::apply_patch(patch, buffers);

        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(interval, patch, buffers);
        set_property_from_patch(playing, patch, buffers);
        set_property_from_patch(repeat, patch, buffers);
        set_property_from_patch(show_repeat, patch, buffers);
        set_property_from_patch(step, patch, buffers);
    }

    template <class D>
    inline xplay<D>::xplay()
    {
        set_defaults();
    }

    template <class D>
    inline void xplay<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_model_name() = "PlayModel";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_name() = "PlayView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xplay>;
    extern template class xtransport<xmaterialize<xplay>>;
}

#endif
