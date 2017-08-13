#ifndef XWIDGET_HPP
#define XWIDGET_HPP

#include <string>

#include "xobject.hpp"

namespace xeus
{

    template <class D>
    class xstyle : public xobject<xstyle<D>>
    {
    public:

        using base_type = xobject<xstyle<D>>;

        xstyle();

    private:

        void set_defaults();
    };

    class xlayout final : public xobject<xlayout>
    {
    public:

        using base_type = xobject<xlayout>;

        xlayout();

        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(X_CASELESS_STR_ENUM(flex-start, flex-end, center, space-between, space-around, space-evenly, stretch, inherit, inital, unset), xlayout, align_content);
        XPROPERTY(X_CASELESS_STR_ENUM(flex-start, flex-end, center, baseline, stretch, inherit, inital, unset), xlayout, align_items);
        XPROPERTY(X_CASELESS_STR_ENUM(auto, flex-start, flex-end, center, baseline, stretch, inherit, inital, unset), xlayout, align_self);
        XPROPERTY(std::string, xlayout, bottom);
        XPROPERTY(std::string, xlayout, border);
        XPROPERTY(std::string, xlayout, display);
        XPROPERTY(std::string, xlayout, flex);
        XPROPERTY(std::string, xlayout, flex_flow);
        XPROPERTY(std::string, xlayout, height);
        XPROPERTY(X_CASELESS_STR_ENUM(flex-start, flex-end, center, space-between, space-around, inherit, inital, unset), xlayout, justify_content);
        XPROPERTY(std::string, xlayout, left);
        XPROPERTY(std::string, xlayout, margin);
        XPROPERTY(std::string, xlayout, max_height);
        XPROPERTY(std::string, xlayout, max_width);
        XPROPERTY(std::string, xlayout, min_height);
        XPROPERTY(std::string, xlayout, min_width);
        XPROPERTY(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset), xlayout, overflow);
        XPROPERTY(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset), xlayout, overflow_x);
        XPROPERTY(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset), xlayout, overflow_y);
        XPROPERTY(std::string, xlayout, order);
        XPROPERTY(std::string, xlayout, padding);
        XPROPERTY(std::string, xlayout, right);
        XPROPERTY(std::string, xlayout, top);
        XPROPERTY(std::string, xlayout, visibility);
        XPROPERTY(std::string, xlayout, width);

    private:

        void set_defaults();
    };

    template <class D>
    class xwidget : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xwidget();
    
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(xlayout, derived_type, layout);

    private:

        void set_defaults();
    };

    /*************************
     * xstyle implementation *
     *************************/

    template <class D>
    inline xstyle<D>::xstyle()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xstyle<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/base";
        this->_view_module() = "@jupyter-widgets/base";
        this->_model_name() = "StyleModel";
        this->_view_name() = "StyleView";
    }

    /**************************
     * xlayout implementation *
     **************************/

    inline xlayout::xlayout()
        : base_type()
    {
        set_defaults();
        this->open();
    }

    inline void xlayout::apply_patch(const xjson& patch)
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

    inline xjson xlayout::get_state() const
    {
        xjson state = base_type::get_state();

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

    inline void xlayout::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/base";
        this->_view_module() = "@jupyter-widgets/base";
        this->_model_name() = "LayoutModel";
        this->_view_name() = "LayoutView";
    }

    /**************************
     * xwidget implementation *
     **************************/

    template <class D>
    inline xwidget<D>::xwidget()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xwidget<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(layout, patch);
    }

    template <class D>
    inline xjson xwidget<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(layout, state);

        return state;
    }

    template <class D>
    inline void xwidget<D>::set_defaults()
    {
        this->_model_name() = "DOMWidgetModel";
        this->_view_name() = "DOMWidgetView";
    }
}

#endif
