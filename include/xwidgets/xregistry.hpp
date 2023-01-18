/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_REGISTRY_HPP
#define XWIDGETS_REGISTRY_HPP

#include <unordered_map>

#include "xeus/xguid.hpp"
#include "xholder.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
    /*************************
     * xregistry declaration *
     *************************/

    template <class D>
    class xtransport;

    class xregistry
    {
    public:

        using holder_type = xholder;
        using storage_type = std::unordered_map<xeus::xguid, holder_type>;

        template <class D>
        void register_weak(xtransport<D>* ptr);

        template <class D>
        void register_owning(xtransport<D>&& model);

        XWIDGETS_API void unregister(xeus::xguid id);

        XWIDGETS_API typename storage_type::mapped_type& find(xeus::xguid id);

    private:

        storage_type m_storage;
    };

    XWIDGETS_API xregistry& get_transport_registry();

    /****************************
     * xregistry implementation *
     ****************************/

    template <class D>
    void xregistry::register_weak(xtransport<D>* ptr)
    {
        m_storage[ptr->id()] = make_weak_holder(ptr);
    }

    template <class D>
    void xregistry::register_owning(xtransport<D>&& model)
    {
        m_storage[model.id()] = make_owning_holder(std::move(model));
    }
}

#endif
