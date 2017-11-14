/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_CONTROLLER_HPP
#define XWIDGETS_CONTROLLER_HPP

#include <string>
#include <vector>

#include "xeus/xjson.hpp"

#include "xmaterialize.hpp"
#include "xwidget.hpp"

namespace xw
{
    /**********************************
     * xcontroller_button declaration *
     **********************************/

    template <class D>
    class xcontroller_button : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(double, derived_type, value);
        XPROPERTY(bool, derived_type, pressed);

    protected:

        xcontroller_button();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using controller_button = xmaterialize<xcontroller_button>;

    using controller_button_generator = xgenerator<xcontroller_button>;

    /********************************
     * xcontroller_axis declaration *
     ********************************/

    template <class D>
    class xcontroller_axis : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;
        using base_type::base_type;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(double, derived_type, value);

    protected:

        xcontroller_axis();

    private:

        void set_defaults();
    };

    using controller_axis = xmaterialize<xcontroller_axis>;

    using controller_axis_generator = xgenerator<xcontroller_axis>;

    /***************************
     * xcontroller declaration *
     ***************************/

    template <class D>
    class xcontroller : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;
        using base_type::base_type;

        using xcontroller_axis_list_type = std::vector<xholder<xtransport>>;
        using xcontroller_button_list_type = std::vector<xholder<xtransport>>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(int, derived_type, index);
        XPROPERTY(std::string, derived_type, name);
        XPROPERTY(std::string, derived_type, mapping)
        XPROPERTY(bool, derived_type, connected);
        XPROPERTY(double, derived_type, timestamp);
        XPROPERTY(xcontroller_button_list_type, derived_type, buttons);
        XPROPERTY(xcontroller_axis_list_type, derived_type, axes);

    protected:

        xcontroller();

    private:

        void set_defaults();

        static int register_control_types();
    };

    using controller = xmaterialize<xcontroller>;

    using controller_generator = xmaterialize<xcontroller>;

    /*************************************
     * xcontroller_button implementation *
     *************************************/

    template <class D>
    inline xeus::xjson xcontroller_button<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(pressed, state);

        return state;
    }

    template <class D>
    inline void xcontroller_button<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(pressed, patch)
    }

    template <class D>
    inline xcontroller_button<D>::xcontroller_button()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcontroller_button<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ControllerButtonModel";
        this->_view_name() = "ControllerButtonView";
    }

    /***********************************
     * xcontroller_axis implementation *
     ***********************************/

    template <class D>
    inline xeus::xjson xcontroller_axis<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(value, state);

        return state;
    }

    template <class D>
    inline void xcontroller_axis<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(value, patch)
    }

    template <class D>
    inline xcontroller_axis<D>::xcontroller_axis()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcontroller_axis<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ControllerAxisModel";
        this->_view_name() = "ControllerAxisView";
    }

    /******************************
     * xcontroller implementation *
     ******************************/

    template <class D>
    inline xeus::xjson xcontroller<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(index, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(name, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(mapping, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(connected, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(timestamp, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(buttons, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(axes, state);

        return state;
    }

    template <class D>
    inline void xcontroller<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(index, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(name, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(mapping, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(connected, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(timestamp, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(buttons, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(axes, patch)
    }

    template <class D>
    inline xcontroller<D>::xcontroller()
        : base_type()
    {
        static int init = register_control_types();
        set_defaults();
    }

    template <class D>
    inline void xcontroller<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ControllerModel";
        this->_view_name() = "ControllerView";
    }

    template <class D>
    inline int xcontroller<D>::register_control_types()
    {
        get_xfactory().register_maker("@jupyter-widgets/controls",
                                      "ControllerAxisModel",
                                      "@jupyter-widgets/controls",
                                      "ControllerAxisView",
                                      xmaker<xcontroller_axis>);

        get_xfactory().register_maker("@jupyter-widgets/controls",
                                      "ControllerButtonModel",
                                      "@jupyter-widgets/controls",
                                      "ControllerButtonView",
                                      xmaker<xcontroller_button>);
        return 0;
    }
}
#endif
