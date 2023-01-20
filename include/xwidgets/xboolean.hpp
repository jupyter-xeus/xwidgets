/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_BOOLEAN_HPP
#define XWIDGETS_BOOLEAN_HPP

#include <string>

#include "xwidget.hpp"

namespace xw
{

    /*****************************
     * base xboolean declaration *
     *****************************/

    template <class D>
    class xboolean : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, value);

    protected:

        xboolean();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /***************************
     * xboolean implementation *
     ***************************/

    template <class D>
    inline void xboolean<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description(), state["description"], buffers);
        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(value(), state["value"], buffers);
    }

    template <class D>
    inline void xboolean<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description, patch, buffers);
        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline xboolean<D>::xboolean()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xboolean<D>::set_defaults()
    {
        this->_model_name() = "BoolModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }
}

#endif
