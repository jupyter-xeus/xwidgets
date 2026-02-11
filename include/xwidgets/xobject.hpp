/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XOBJECT_HPP
#define XOBJECT_HPP

#include <optional>
#include <string>

#include "xjson.hpp"
#include "xmaterialize.hpp"
#include "xtransport.hpp"

namespace xw
{
    /***********************
     * xobject declaration *
     ***********************/

    template <class D>
    class xobject : public xtransport<D>
    {
    public:

        using base_type = xtransport<D>;
        using derived_type = D;

        using base_type::derived_cast;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::optional<std::string>, xcommon, _model_module, "@jupyter-widgets/base");
        XPROPERTY(std::optional<std::string>, xcommon, _model_module_version, XWIDGETS_BASE_VERSION);
        XPROPERTY(std::optional<std::string>, xcommon, _model_name, "WidgetModel");
        XPROPERTY(std::optional<std::string>, xcommon, _view_module, "@jupyter-widgets/base");
        XPROPERTY(std::optional<std::string>, xcommon, _view_module_version, XWIDGETS_BASE_VERSION);
        XPROPERTY(std::optional<std::string>, xcommon, _view_name, "WidgetView");

    protected:

        xobject() = default;

        using base_type::base_type;
    };

    /**************************
     * xobject implementation *
     **************************/

    template <class D>
    inline void xobject<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        xwidgets_serialize(_model_module(), state["_model_module"], buffers);
        xwidgets_serialize(_model_module_version(), state["_model_module_version"], buffers);
        xwidgets_serialize(_model_name(), state["_model_name"], buffers);
        xwidgets_serialize(_view_module(), state["_view_module"], buffers);
        xwidgets_serialize(_view_module_version(), state["_view_module_version"], buffers);
        xwidgets_serialize(_view_name(), state["_view_name"], buffers);
    }

    template <class D>
    inline void xobject<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        this->apply_patch_to_registered_properties(patch, buffers);
    }
}

#endif
