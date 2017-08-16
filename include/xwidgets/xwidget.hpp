#ifndef XWIDGET_HPP
#define XWIDGET_HPP

#include <string>

#include "xobject.hpp"

namespace xeus
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

        xlayout();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(flex-start, flex-end, center, space-between, space-around, space-evenly, stretch, inherit, inital, unset)), derived_type, align_content);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(flex-start, flex-end, center, baseline, stretch, inherit, inital, unset)), derived_type, align_items);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(auto, flex-start, flex-end, center, baseline, stretch, inherit, inital, unset)), derived_type, align_self);
        XPROPERTY(XOPTIONAL(std::string), derived_type, bottom);
        XPROPERTY(XOPTIONAL(std::string), derived_type, border);
        XPROPERTY(XOPTIONAL(std::string), derived_type, display);
        XPROPERTY(XOPTIONAL(std::string), derived_type, flex);
        XPROPERTY(XOPTIONAL(std::string), derived_type, flex_flow);
        XPROPERTY(XOPTIONAL(std::string), derived_type, height);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(flex-start, flex-end, center, space-between, space-around, inherit, inital, unset)), derived_type, justify_content);
        XPROPERTY(XOPTIONAL(std::string), derived_type, left);
        XPROPERTY(XOPTIONAL(std::string), derived_type, margin);
        XPROPERTY(XOPTIONAL(std::string), derived_type, max_height);
        XPROPERTY(XOPTIONAL(std::string), derived_type, max_width);
        XPROPERTY(XOPTIONAL(std::string), derived_type, min_height);
        XPROPERTY(XOPTIONAL(std::string), derived_type, min_width);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset)), derived_type, overflow);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset)), derived_type, overflow_x);
        XPROPERTY(XOPTIONAL(X_CASELESS_STR_ENUM(visible, hidden, scroll, auto, inherit, inital, unset)), derived_type, overflow_y);
        XPROPERTY(XOPTIONAL(std::string), derived_type, order);
        XPROPERTY(XOPTIONAL(std::string), derived_type, padding);
        XPROPERTY(XOPTIONAL(std::string), derived_type, right);
        XPROPERTY(XOPTIONAL(std::string), derived_type, top);
        XPROPERTY(XOPTIONAL(std::string), derived_type, visibility);
        XPROPERTY(XOPTIONAL(std::string), derived_type, width);

    private:

        void set_defaults();
    };

    class layout final : public xlayout<layout>
    {
    public:

        using base_type = xlayout<layout>;

        layout() : base_type()
        {
            this->open();
        }

        layout(const layout& other) : base_type(other)
        {
           this->open();
        }

        layout(layout&&) = default;

        layout& operator=(const layout& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }

        layout& operator=(layout&&) = default;
    };

    /*****************************************
     * base xstyle and xwidgets declarations *
     *****************************************/

    template <class D>
    class xstyle : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        xstyle();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

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

        XPROPERTY(::xeus::layout, derived_type, layout);

    private:

        void set_defaults();
    };

    /*************************
     * layout implementation *
     *************************/

    template <class D>
    inline xlayout<D>::xlayout()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlayout<D>::apply_patch(const xjson& patch)
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
    inline xjson xlayout<D>::get_state() const
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

    template <class D>
    inline void xlayout<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/base";
        this->_view_module() = "@jupyter-widgets/base";
        this->_model_name() = "LayoutModel";
        this->_view_name() = "LayoutView";
    }

    /********************************************
     * base xstyle and xwidgets implementations *
     ********************************************/

    template <class D>
    inline xstyle<D>::xstyle()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xstyle<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xjson xstyle<D>::get_state() const
    {
        xjson state = base_type::get_state();
        return state;
    }

    template <class D>
    inline void xstyle<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/base";
        this->_view_module() = "@jupyter-widgets/base";
        this->_model_name() = "StyleModel";
        this->_view_name() = "StyleView";
    }

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
