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
#include "xnumber.hpp"

namespace xw
{
    /********************
     * play declaration *
     ********************/

    template <class D>
    class xplay : public xnumber<D>
    {
    public:

        using base_type = xnumber<D>;
        using derived_type = D;

        using value_type = typename base_type::value_type;

        void serialize_state(nl::json& state, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, interval, value_type(100));
        XPROPERTY(value_type, derived_type, step, value_type(1));
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, _playing);
        XPROPERTY(bool, derived_type, _repeat);
        XPROPERTY(bool, derived_type, show_repeat, true);

    protected:

        xplay();
        using base_type::base_type;

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

        xwidgets_serialize(interval(), state["interval"], buffers);
        xwidgets_serialize(step(), state["step"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(_playing(), state["_playing"], buffers);
        xwidgets_serialize(_repeat(), state["_repeat"], buffers);
        xwidgets_serialize(show_repeat(), state["show_repeat"], buffers);
    }

    template <class D>
    inline void xplay<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(interval, patch, buffers);
        set_property_from_patch(step, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(_playing, patch, buffers);
        set_property_from_patch(_repeat, patch, buffers);
        set_property_from_patch(show_repeat, patch, buffers);
    }

    template <class D>
    inline xplay<D>::xplay()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xplay<D>::set_defaults()
    {
        this->_model_name() = "PlayModel";
        this->_view_name() = "PlayView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xplay>;
    extern template class xtransport<xmaterialize<xplay>>;
}

#endif
