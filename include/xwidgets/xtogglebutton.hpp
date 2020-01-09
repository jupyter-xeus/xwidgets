/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TOGGLE_HPP
#define XWIDGETS_TOGGLE_HPP

#include <string>

#include "xboolean.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"

namespace xw
{
    /****************************
     * togglebutton declaration *
     ****************************/

    template <class D>
    class xtogglebutton : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, tooltip);
        XPROPERTY(std::string, derived_type, icon);
        XPROPERTY(std::string, derived_type, button_style, "", XEITHER("primary", "success", "info", "warning", "danger", ""));

    protected:

        xtogglebutton();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebutton = xmaterialize<xtogglebutton>;

    using togglebutton_generator = xgenerator<xtogglebutton>;

    /********************************
     * xtogglebutton implementation *
     ********************************/

    template <class D>
    inline xtogglebutton<D>::xtogglebutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtogglebutton<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(tooltip(), state["tooltip"], buffers);
        xwidgets_serialize(icon(), state["icon"], buffers);
        xwidgets_serialize(button_style(), state["button_style"], buffers);
    }

    template <class D>
    inline void xtogglebutton<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(tooltip, patch, buffers);
        set_property_from_patch(icon, patch, buffers);
        set_property_from_patch(button_style, patch, buffers);
    }

    template <class D>
    inline void xtogglebutton<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonModel";
        this->_view_name() = "ToggleButtonView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xtogglebutton>;
    extern template xmaterialize<xtogglebutton>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebutton>>;
    extern template class xgenerator<xtogglebutton>;
    extern template xgenerator<xtogglebutton>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebutton>>;
#endif
}

#endif
