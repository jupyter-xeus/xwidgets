/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TOGGLEBUTTONS_HPP
#define XWIDGETS_TOGGLEBUTTONS_HPP

#include <string>
#include <utility>
#include <vector>

#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xselection.hpp"
#include "xstyle.hpp"

namespace xw
{
    /***********************************
     * togglebuttons_style declaration *
     ***********************************/

    template <class D>
    class xtogglebuttons_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, button_width);

    protected:

        xtogglebuttons_style();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebuttons_style = xmaterialize<xtogglebuttons_style>;

    /*****************************
     * togglebuttons declaration *
     *****************************/

    template <class D>
    class xtogglebuttons : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xtogglebuttons();

        template <class O, class T>
        xtogglebuttons(O&& options, T&& value);

        using base_type::base_type;

        XPROPERTY(std::vector<std::string>, derived_type, tooltips);
        XPROPERTY(std::vector<std::string>, derived_type, icons);
        XPROPERTY(::xw::togglebuttons_style, derived_type, style);
        XPROPERTY(std::string, derived_type, button_style, "", XEITHER("primary", "success", "info", "warning", "danger", ""));

    private:

        void set_defaults();
    };

    using togglebuttons = xmaterialize<xtogglebuttons>;

    /***************************************
     * xtogglebuttons_style implementation *
     ***************************************/

    template <class D>
    inline void xtogglebuttons_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(button_width(), state["button_width"], buffers);
    }

    template <class D>
    inline void xtogglebuttons_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(button_width, patch, buffers);
    }

    template <class D>
    inline xtogglebuttons_style<D>::xtogglebuttons_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtogglebuttons_style<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonsStyleModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************************
     * xtogglebuttons implementation *
     *********************************/

    template <class D>
    inline void xtogglebuttons<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(tooltips(), state["tooltips"], buffers);
        xwidgets_serialize(icons(), state["icons"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
        xwidgets_serialize(button_style(), state["button_style"], buffers);
    }

    template <class D>
    inline void xtogglebuttons<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(tooltips, patch, buffers);
        set_property_from_patch(icons, patch, buffers);
        set_property_from_patch(style, patch, buffers);
        set_property_from_patch(button_style, patch, buffers);
    }

    template <class D>
    inline xtogglebuttons<D>::xtogglebuttons()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class O, class T>
    inline xtogglebuttons<D>::xtogglebuttons(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xtogglebuttons<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonsModel";
        this->_view_name() = "ToggleButtonsView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xtogglebuttons_style>;
    extern template xmaterialize<xtogglebuttons_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons_style>>;

    extern template class xmaterialize<xtogglebuttons>;
    extern template xmaterialize<xtogglebuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons>>;
#endif
}
#endif
