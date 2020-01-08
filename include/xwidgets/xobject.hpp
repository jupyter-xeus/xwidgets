/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XOBJECT_HPP
#define XOBJECT_HPP

#include <string>
#include <unordered_map>

#include "xtl/xoptional.hpp"
#include "xtl/xjson.hpp"

#include "xproperty/xobserved.hpp"

#include "xmaterialize.hpp"
#include "xtransport.hpp"

namespace xw
{
    /****************************
     * base xobject declaration *
     ****************************/

    template <class D>
    class xobject : public xp::xobserved<D>, public xtransport<D>
    {
    public:

        using base_type = xtransport<D>;
        using derived_type = D;

        using base_type::derived_cast;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<std::string>, derived_type, _model_module, "@jupyter-widgets/base");
        XPROPERTY(xtl::xoptional<std::string>, derived_type, _model_module_version, XWIDGETS_BASE_VERSION);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, _model_name, "WidgetModel");
        XPROPERTY(xtl::xoptional<std::string>, derived_type, _view_module, "@jupyter-widgets/base");
        XPROPERTY(xtl::xoptional<std::string>, derived_type, _view_module_version, XWIDGETS_BASE_VERSION);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, _view_name, "WidgetView");

        using base_type::notify;

    protected:

        xobject();
        xobject(xeus::xcomm&&, bool owning = false);
        using concrete_type = xconcrete_type_t<D>;

        concrete_type* self();
        const concrete_type* self() const;
    };

    /*******************************
     * base xobject implementation *
     *******************************/

    template <class D>
    inline void xobject<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        set_patch_from_property(_model_module, state, buffers);
        set_patch_from_property(_model_module_version, state, buffers);
        set_patch_from_property(_model_name, state, buffers);
        set_patch_from_property(_view_module, state, buffers);
        set_patch_from_property(_view_module_version, state, buffers);
        set_patch_from_property(_view_name, state, buffers);
    }

    template <class D>
    inline void xobject<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        set_property_from_patch(_model_module, patch, buffers);
        set_property_from_patch(_model_module_version, patch, buffers);
        set_property_from_patch(_model_name, patch, buffers);
        set_property_from_patch(_view_module, patch, buffers);
        set_property_from_patch(_view_module_version, patch, buffers);
        set_property_from_patch(_view_name, patch, buffers);
    }

    template <class D>
    inline xobject<D>::xobject()
        : base_type()
    {
    }

    template <class D>
    inline xobject<D>::xobject(xeus::xcomm&& com, bool owning)
        : base_type(std::move(com), owning)
    {
    }

    template <class D>
    inline auto xobject<D>::self() -> concrete_type*
    {
        return reinterpret_cast<concrete_type*>(this);
    }

    template <class D>
    inline auto xobject<D>::self() const -> const concrete_type*
    {
        return reinterpret_cast<const concrete_type*>(this);
    }
}

#endif
