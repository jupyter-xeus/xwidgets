/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xregistry.hpp"

namespace xw
{
    void xregistry::unregister(xeus::xguid id)
    {
        m_storage.erase(id);
    }

    auto xregistry::find(xeus::xguid id) -> typename storage_type::mapped_type&
    {
        auto it = m_storage.find(id);
        if (it == m_storage.end())
        {
            throw std::runtime_error("Could not find specified id in transport registry");
        }
        return it->second;
    }

    auto xregistry::begin() const -> const_iterator
    {
        return cbegin();
    }

    auto xregistry::cbegin() const -> const_iterator
    {
        return m_storage.cbegin();
    }

    auto xregistry::end() const -> const_iterator
    {
        return cend();
    }

    auto xregistry::cend() const -> const_iterator
    {
        return m_storage.cend();
    }

    xregistry& get_transport_registry()
    {
        static xregistry instance;
        return instance;
    }
}
