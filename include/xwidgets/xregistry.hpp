#ifndef XWIDGETS_REGISTRY_HPP
#define XWIDGETS_REGISTRY_HPP

#include <unordered_map>
#include <utility>

#include "xholder.hpp" 
#include "xtransport.hpp"

namespace xw
{
    /*************************
     * xregistry declaration *
     *************************/

    class xregistry
    {
    public:

        using storage_type = std::unordered_map<std::string, xholder<xtransport>>;

        template <class D>
        void register_weak(xtransport<D>* ptr);

        void unregister(xeus::xguid id);

        typename storage_type::mapped_type& find(xeus::xguid id);

    private:

        storage_type m_storage;
    };

    inline xregistry& get_transport_registry()
    {
        static xregistry instance;
        return instance;
    }

    /****************************
     * xregistry implementation *
     ****************************/

    template <class D>
    void xregistry::register_weak(xtransport<D>* ptr)
    {
        m_storage[xeus::guid_to_hex(ptr->id())] = make_weak_holder(ptr);
    }

    void xregistry::unregister(xeus::xguid id)
    {
        m_storage.erase(xeus::guid_to_hex(id));
    }

    auto xregistry::find(xeus::xguid id) -> typename storage_type::mapped_type&
    {
        auto it = m_storage.find(xeus::guid_to_hex(id));
        if (it == m_storage.end())
        {
            throw std::runtime_error("Could not find specified id in widgets registry");
        }
        return it->second;
    }
}
#endif

