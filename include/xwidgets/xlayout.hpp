/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_LAYOUT_HPP
#define XWIDGETS_LAYOUT_HPP

#include <optional>
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

        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            align_content,
            {},
            XEITHER_OPTIONAL(
                "flex-start",
                "flex-end",
                "center",
                "space-between",
                "space-around",
                "space-evenly",
                "stretch",
                "inherit",
                "inital",
                "unset"
            )
        );
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            align_items,
            {},
            XEITHER_OPTIONAL("flex-start", "flex-end", "center", "baseline", "stretch", "inherit", "inital", "unset")
        );
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            align_self,
            {},
            XEITHER_OPTIONAL("auto", "flex-start", "flex-end", "center", "baseline", "stretch", "inherit", "inital", "unset")
        );
        XPROPERTY(std::optional<std::string>, xcommon, border_bottom);
        XPROPERTY(std::optional<std::string>, xcommon, border_left);
        XPROPERTY(std::optional<std::string>, xcommon, border_right);
        XPROPERTY(std::optional<std::string>, xcommon, border_top);
        XPROPERTY(std::optional<std::string>, xcommon, bottom);
        XPROPERTY(std::optional<std::string>, xcommon, display);
        XPROPERTY(std::optional<std::string>, xcommon, flex);
        XPROPERTY(std::optional<std::string>, xcommon, flex_flow);
        XPROPERTY(std::optional<std::string>, xcommon, grid_area);
        XPROPERTY(std::optional<std::string>, xcommon, grid_auto_columns);
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            grid_auto_flow,
            {},
            XEITHER_OPTIONAL("column", "row", "row dense", "column dense", "inherit", "initial", "unset")
        );
        XPROPERTY(std::optional<std::string>, xcommon, grid_auto_rows);
        XPROPERTY(std::optional<std::string>, xcommon, grid_column);
        XPROPERTY(std::optional<std::string>, xcommon, grid_gap);
        XPROPERTY(std::optional<std::string>, xcommon, grid_row);
        XPROPERTY(std::optional<std::string>, xcommon, grid_template_areas);
        XPROPERTY(std::optional<std::string>, xcommon, grid_template_columns);
        XPROPERTY(std::optional<std::string>, xcommon, grid_template_rows);
        XPROPERTY(std::optional<std::string>, xcommon, height);
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            justify_content,
            {},
            XEITHER_OPTIONAL("flex-start", "flex-end", "center", "space-between", "space-around", "inherit", "inital", "unset")
        );
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            justify_items,
            {},
            XEITHER_OPTIONAL("flex-start", "flex-end", "center", "inherit", "initial", "unset")
        );
        XPROPERTY(std::optional<std::string>, xcommon, left);
        XPROPERTY(std::optional<std::string>, xcommon, margin);
        XPROPERTY(std::optional<std::string>, xcommon, max_height);
        XPROPERTY(std::optional<std::string>, xcommon, max_width);
        XPROPERTY(std::optional<std::string>, xcommon, min_height);
        XPROPERTY(std::optional<std::string>, xcommon, min_width);
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            object_fit,
            {},
            XEITHER_OPTIONAL("contain", "cover", "fill", "scale-down", "none")
        );
        XPROPERTY(std::optional<std::string>, xcommon, object_position);
        XPROPERTY(std::optional<std::string>, xcommon, order);
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            overflow,
            {},
            XEITHER_OPTIONAL("visible", "hidden", "scroll", "auto", "inherit", "inital", "unset")
        );
        XPROPERTY(std::optional<std::string>, xcommon, padding);
        XPROPERTY(std::optional<std::string>, xcommon, right);
        XPROPERTY(std::optional<std::string>, xcommon, top);
        XPROPERTY(
            std::optional<std::string>,
            xcommon,
            visibility,
            {},
            XEITHER_OPTIONAL("visible", "hidden", "inherit", "initial", "unset")
        );
        XPROPERTY(std::optional<std::string>, xcommon, width);

    protected:

        xlayout();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using layout = xmaterialize<xlayout>;

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
        xwidgets_serialize(border_bottom(), state["border_bottom"], buffers);
        xwidgets_serialize(border_left(), state["border_left"], buffers);
        xwidgets_serialize(border_right(), state["border_right"], buffers);
        xwidgets_serialize(border_top(), state["border_top"], buffers);
        xwidgets_serialize(bottom(), state["bottom"], buffers);
        xwidgets_serialize(display(), state["display"], buffers);
        xwidgets_serialize(flex(), state["flex"], buffers);
        xwidgets_serialize(flex_flow(), state["flex_flow"], buffers);
        xwidgets_serialize(grid_area(), state["grid_area"], buffers);
        xwidgets_serialize(grid_auto_columns(), state["grid_auto_columns"], buffers);
        xwidgets_serialize(grid_auto_flow(), state["grid_auto_flow"], buffers);
        xwidgets_serialize(grid_auto_rows(), state["grid_auto_rows"], buffers);
        xwidgets_serialize(grid_column(), state["grid_column"], buffers);
        xwidgets_serialize(grid_gap(), state["grid_gap"], buffers);
        xwidgets_serialize(grid_row(), state["grid_row"], buffers);
        xwidgets_serialize(grid_template_areas(), state["grid_template_areas"], buffers);
        xwidgets_serialize(grid_template_columns(), state["grid_template_columns"], buffers);
        xwidgets_serialize(grid_template_rows(), state["grid_template_rows"], buffers);
        xwidgets_serialize(height(), state["height"], buffers);
        xwidgets_serialize(justify_content(), state["justify_content"], buffers);
        xwidgets_serialize(justify_items(), state["justify_items"], buffers);
        xwidgets_serialize(left(), state["left"], buffers);
        xwidgets_serialize(margin(), state["margin"], buffers);
        xwidgets_serialize(max_height(), state["max_height"], buffers);
        xwidgets_serialize(max_width(), state["max_width"], buffers);
        xwidgets_serialize(min_height(), state["min_height"], buffers);
        xwidgets_serialize(min_width(), state["min_width"], buffers);
        xwidgets_serialize(object_fit(), state["object_fit"], buffers);
        xwidgets_serialize(object_position(), state["object_position"], buffers);
        xwidgets_serialize(order(), state["order"], buffers);
        xwidgets_serialize(overflow(), state["overflow"], buffers);
        xwidgets_serialize(padding(), state["padding"], buffers);
        xwidgets_serialize(right(), state["right"], buffers);
        xwidgets_serialize(top(), state["top"], buffers);
        xwidgets_serialize(visibility(), state["visibility"], buffers);
        xwidgets_serialize(width(), state["width"], buffers);
    }

    template <class D>
    inline void xlayout<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xlayout<D>::xlayout()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayout<D>::set_defaults()
    {
        this->_model_name() = "LayoutModel";
        this->_view_name() = "LayoutView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xlayout>;
    extern template class xtransport<xmaterialize<xlayout>>;
}
#endif
