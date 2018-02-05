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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, button_width);

    protected:

        xtogglebuttons_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using togglebuttons_style = xmaterialize<xtogglebuttons_style>;

    using togglebuttons_style_generator = xgenerator<xtogglebuttons_style>;

    /*****************************
     * togglebuttons declaration *
     *****************************/

    template <class D>
    class xtogglebuttons : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

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

    using togglebuttons_generator = xgenerator<xtogglebuttons>;

    /***************************************
     * xtogglebuttons_style implementation *
     ***************************************/

    template <class D>
    inline xeus::xjson xtogglebuttons_style<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(button_width, state);

        return state;
    }

    template <class D>
    inline void xtogglebuttons_style<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_width, patch);
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ToggleButtonsStyleModel";
    }

    /*********************************
     * xtogglebuttons implementation *
     *********************************/

    template <class D>
    inline xeus::xjson xtogglebuttons<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltips, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(icons, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(button_style, state);

        return state;
    }

    template <class D>
    inline void xtogglebuttons<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltips, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(icons, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_style, patch);
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ToggleButtonsModel";
        this->_view_name() = "ToggleButtonsView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xtogglebuttons_style>;
    extern template xmaterialize<xtogglebuttons_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons_style>>;
    extern template class xgenerator<xtogglebuttons_style>;
    extern template xgenerator<xtogglebuttons_style>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebuttons_style>>;

    extern template class xmaterialize<xtogglebuttons>;
    extern template xmaterialize<xtogglebuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons>>;
    extern template class xgenerator<xtogglebuttons>;
    extern template xgenerator<xtogglebuttons>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebuttons>>;
}
#endif
