/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_LAYOUT_HPP
#define XWIDGETS_LAYOUT_HPP

#include <string>

#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xobject.hpp"

namespace xw
{
    /**********************
     * layout declaration *
     **********************/

    template <class D>
    class xlayout : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(xtl::xoptional<std::string>, derived_type, align_content, {}, XEITHER_OPTIONAL("flex-start", "flex-end", "center", "space-between", "space-around", "space-evenly", "stretch", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, align_items, {}, XEITHER_OPTIONAL("flex-start", "flex-end", "center", "baseline", "stretch", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, align_self, {}, XEITHER_OPTIONAL("auto", "flex-start", "flex-end", "center", "baseline", "stretch", "inherit", "inital", "unset"));

        XPROPERTY(xtl::xoptional<std::string>, derived_type, bottom);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, border);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, display);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, flex);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, flex_flow);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, height);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, justify_content, {}, XEITHER_OPTIONAL("flex-start", "flex-end", "center", "space-between", "space-around", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, left);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, margin);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, max_height);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, max_width);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, min_height);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, min_width);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, overflow, {}, XEITHER_OPTIONAL("visible", "hidden", "scroll", "auto", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, overflow_x, {}, XEITHER_OPTIONAL("visible", "hidden", "scroll", "auto", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, overflow_y, {}, XEITHER_OPTIONAL("visible", "hidden", "scroll", "auto", "inherit", "inital", "unset"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, order);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, padding);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, right);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, top);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, visibility);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, width);

    protected:

        xlayout();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using layout = xmaterialize<xlayout>;

    using layout_generator = xgenerator<xlayout>;

    /*************************
     * layout implementation *
     *************************/

    template <class D>
    inline void xlayout<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(align_content, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(align_items, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(align_self, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bottom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(border, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(display, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(flex, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(flex_flow, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(height, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(justify_content, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(left, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(margin, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_height, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(overflow, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(overflow_x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(overflow_y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(order, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(padding, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(right, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(top, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(width, patch);
    }

    template <class D>
    inline xeus::xjson xlayout<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(align_content, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(align_items, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(align_self, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bottom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(border, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(display, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(flex, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(flex_flow, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(height, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(justify_content, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(left, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(margin, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_height, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_height, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(overflow, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(overflow_x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(overflow_y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(order, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(padding, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(right, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(top, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(width, state);

        return state;
    }

    template <class D>
    inline xlayout<D>::xlayout()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayout<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/base";
        this->_view_module() = "@jupyter-widgets/base";
        this->_model_name() = "LayoutModel";
        this->_view_name() = "LayoutView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xlayout>;
    extern template xmaterialize<xlayout>::xmaterialize();
    extern template class xtransport<xmaterialize<xlayout>>;
    extern template class xgenerator<xlayout>;
    extern template xgenerator<xlayout>::xgenerator();
    extern template class xtransport<xgenerator<xlayout>>;
#endif
}
#endif
