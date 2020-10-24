#include "xwidgets/xholder.hpp"
// TODO: separate xregistry declaration in own header

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
    
    xregistry& get_transport_registry()
    {
        static xregistry instance;
        return instance;
    }
}
