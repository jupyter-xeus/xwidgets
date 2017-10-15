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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

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

    using play_generator = xgenerator<xplay>;

    template <>
    struct xnumber_traits<play>
    {
        using value_type = int;
    };

    /************************
     * xplay implementation *
     ************************/

    template <class D>
    inline xeus::xjson xplay<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(interval, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(step, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_playing, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_repeat, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(show_repeat, state);

        return state;
    }

    template <class D>
    inline void xplay<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(interval, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(step, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(_playing, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(_repeat, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(show_repeat, patch)
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
}

#endif
