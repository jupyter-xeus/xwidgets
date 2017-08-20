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

#include "xproperty/xobserved.hpp"
#include "xtransport.hpp"

namespace xeus
{

    /****************************
     * base xobject declaration *
     ****************************/

    // TODO: Generate an enum type with
    //  - operator=() allowing string assignment
    //  - to_json and from_json overload converting from and to the corresponding strings.
    #define X_CASELESS_STR_ENUM(...) std::string

    // TODO: Use an optional type such as xtensor optionals
    #define XOPTIONAL(x) x

    template <class D>
    class xobject : public xp::xobserved<D>, public xtransport<D>
    {
    public:

        using base_type = xtransport<D>;
        using derived_type = D;

        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(std::string), derived_type, _model_module, "jupyter-js-widgets");
        XPROPERTY(XOPTIONAL(std::string), derived_type, _model_module_version, "~2.1.4");
        XPROPERTY(XOPTIONAL(std::string), derived_type, _model_name, "WidgetModel");
        XPROPERTY(XOPTIONAL(std::string), derived_type, _view_module, "jupyter-js-widgets");
        XPROPERTY(XOPTIONAL(std::string), derived_type, _view_module_version, "~2.1.4");
        XPROPERTY(XOPTIONAL(std::string), derived_type, _view_name, "WidgetView");

        using base_type::notify;
    };

    /*******************************
     * base xobject implementation *
     *******************************/

    #define XOBJECT_SET_PROPERTY_FROM_PATCH(name, patch)                   \
    if (patch.find(#name) != patch.end())                                  \
    {                                                                      \
        name = patch.at(#name).get<typename decltype(name)::value_type>(); \
    }

    #define XOBJECT_SET_PATCH_FROM_PROPERTY(name, patch) \
    patch[#name] = this->name();

    template <class D>
    inline void xobject<D>::apply_patch(const xjson& patch)
    {
        XOBJECT_SET_PROPERTY_FROM_PATCH(_model_module, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_model_module_version, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_model_name, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_view_module, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_view_module_version, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_view_name, patch);
    }

    template <class D>
    inline xjson xobject<D>::get_state() const
    {
        xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_module, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_module_version, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_model_name, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_module, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_module_version, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_view_name, state);
        return state;
    }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    template <class D>
    inline void to_json(xjson& j, const xobject<D>& o)
    {
        j = "IPY_MODEL_" + guid_to_hex(o.id());
    }

    template <class D>
    inline void from_json(const xjson& j, xobject<D>& o)
    {
        // TODO: use a backend widgets instance registry
    }
}

#endif
