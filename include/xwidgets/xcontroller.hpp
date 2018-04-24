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
#include "xmaker.hpp"
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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(double, derived_type, value);

    protected:

        xcontroller_axis();
        using base_type::base_type;

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

#ifdef _MSC_VER
        template <class T>
        using transport_type = xtransport<T>;

        using xcontroller_axis_list_type = std::vector<xholder<transport_type>>;
        using xcontroller_button_list_type = std::vector<xholder<transport_type>>;
#else
        using xcontroller_axis_list_type = std::vector<xholder<xtransport>>;
        using xcontroller_button_list_type = std::vector<xholder<xtransport>>;
#endif

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(int, derived_type, index);
        XPROPERTY(std::string, derived_type, name);
        XPROPERTY(std::string, derived_type, mapping)
        XPROPERTY(bool, derived_type, connected);
        XPROPERTY(double, derived_type, timestamp);
        XPROPERTY(xcontroller_button_list_type, derived_type, buttons);
        XPROPERTY(xcontroller_axis_list_type, derived_type, axes);

    protected:

        xcontroller();
        using base_type::base_type;

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
    inline void xcontroller_button<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(value, state, buffers);
        this->set_patch_from_property(pressed, state, buffers);
    }

    template <class D>
    inline void xcontroller_button<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(value, patch, buffers);
        this->set_property_from_patch(pressed, patch, buffers);
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
        this->_model_name() = "ControllerButtonModel";
        this->_view_name() = "ControllerButtonView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /***********************************
     * xcontroller_axis implementation *
     ***********************************/

    template <class D>
    inline void xcontroller_axis<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(value, state, buffers);
    }

    template <class D>
    inline void xcontroller_axis<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(value, patch, buffers);
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
        this->_model_name() = "ControllerAxisModel";
        this->_view_name() = "ControllerAxisView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /******************************
     * xcontroller implementation *
     ******************************/

    template <class D>
    inline void xcontroller<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(index, state, buffers);
        this->set_patch_from_property(name, state, buffers);
        this->set_patch_from_property(mapping, state, buffers);
        this->set_patch_from_property(connected, state, buffers);
        this->set_patch_from_property(timestamp, state, buffers);
        this->set_patch_from_property(buttons, state, buffers);
        this->set_patch_from_property(axes, state, buffers);
    }

    template <class D>
    inline void xcontroller<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(index, patch, buffers);
        this->set_property_from_patch(name, patch, buffers);
        this->set_property_from_patch(mapping, patch, buffers);
        this->set_property_from_patch(connected, patch, buffers);
        this->set_property_from_patch(timestamp, patch, buffers);
        this->set_property_from_patch(buttons, patch, buffers);
        this->set_property_from_patch(axes, patch, buffers);
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
        this->_model_name() = "ControllerModel";
        this->_view_name() = "ControllerView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
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

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xcontroller_button>;
    extern template xmaterialize<xcontroller_button>::xmaterialize();
    extern template class xtransport<xmaterialize<xcontroller_button>>;
    extern template class xgenerator<xcontroller_button>;
    extern template xgenerator<xcontroller_button>::xgenerator();
    extern template class xtransport<xgenerator<xcontroller_button>>;

    extern template class xmaterialize<xcontroller_axis>;
    extern template xmaterialize<xcontroller_axis>::xmaterialize();
    extern template class xtransport<xmaterialize<xcontroller_axis>>;
    extern template class xgenerator<xcontroller_axis>;
    extern template xgenerator<xcontroller_axis>::xgenerator();
    extern template class xtransport<xgenerator<xcontroller_axis>>;

    extern template class xmaterialize<xcontroller>;
    extern template xmaterialize<xcontroller>::xmaterialize();
    extern template class xtransport<xmaterialize<xcontroller>>;
    extern template class xgenerator<xcontroller>;
    extern template xgenerator<xcontroller>::xgenerator();
    extern template class xtransport<xgenerator<xcontroller>>;
#endif
}

#endif
