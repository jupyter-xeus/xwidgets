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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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
    inline void xlayout<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(align_content(), state["align_content"], buffers);
        xwidgets_serialize(align_items(), state["align_items"], buffers);
        xwidgets_serialize(align_self(), state["align_self"], buffers);
        xwidgets_serialize(bottom(), state["bottom"], buffers);
        xwidgets_serialize(border(), state["border"], buffers);
        xwidgets_serialize(display(), state["display"], buffers);
        xwidgets_serialize(flex(), state["flex"], buffers);
        xwidgets_serialize(flex_flow(), state["flex_flow"], buffers);
        xwidgets_serialize(height(), state["height"], buffers);
        xwidgets_serialize(justify_content(), state["justify_content"], buffers);
        xwidgets_serialize(left(), state["left"], buffers);
        xwidgets_serialize(margin(), state["margin"], buffers);
        xwidgets_serialize(max_height(), state["max_height"], buffers);
        xwidgets_serialize(max_width(), state["max_width"], buffers);
        xwidgets_serialize(min_height(), state["min_height"], buffers);
        xwidgets_serialize(min_width(), state["min_width"], buffers);
        xwidgets_serialize(overflow(), state["overflow"], buffers);
        xwidgets_serialize(overflow_x(), state["overflow_x"], buffers);
        xwidgets_serialize(overflow_y(), state["overflow_y"], buffers);
        xwidgets_serialize(order(), state["order"], buffers);
        xwidgets_serialize(padding(), state["padding"], buffers);
        xwidgets_serialize(right(), state["right"], buffers);
        xwidgets_serialize(top(), state["top"], buffers);
        xwidgets_serialize(width(), state["width"], buffers);
    }

    template <class D>
    inline void xlayout<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(align_content, patch, buffers);
        set_property_from_patch(align_items, patch, buffers);
        set_property_from_patch(align_self, patch, buffers);
        set_property_from_patch(bottom, patch, buffers);
        set_property_from_patch(border, patch, buffers);
        set_property_from_patch(display, patch, buffers);
        set_property_from_patch(flex, patch, buffers);
        set_property_from_patch(flex_flow, patch, buffers);
        set_property_from_patch(height, patch, buffers);
        set_property_from_patch(justify_content, patch, buffers);
        set_property_from_patch(left, patch, buffers);
        set_property_from_patch(margin, patch, buffers);
        set_property_from_patch(max_height, patch, buffers);
        set_property_from_patch(max_width, patch, buffers);
        set_property_from_patch(overflow, patch, buffers);
        set_property_from_patch(overflow_x, patch, buffers);
        set_property_from_patch(overflow_y, patch, buffers);
        set_property_from_patch(order, patch, buffers);
        set_property_from_patch(padding, patch, buffers);
        set_property_from_patch(right, patch, buffers);
        set_property_from_patch(top, patch, buffers);
        set_property_from_patch(width, patch, buffers);
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
