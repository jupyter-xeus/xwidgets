#ifndef XWIDGETS_REGISTRY_HPP
#define XWIDGETS_REGISTRY_HPP

#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "xholder.hpp"
#include "xmaterialize.hpp"

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

        using holder_type = xholder<xtransport>;
        using storage_type = std::unordered_map<xeus::xguid, holder_type>;

        template <class D>
        void register_weak(xtransport<D>* ptr);

        template <class D>
        void register_owning(xtransport<D>&& model);

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
        m_storage[ptr->id()] = make_weak_holder(ptr);
    }

    template <class D>
    void xregistry::register_owning(xtransport<D>&& model)
    {
        return m_storage[model.id()] = make_owning_holder(std::move(model));
    }

    inline void xregistry::unregister(xeus::xguid id)
    {
        m_storage.erase(id);
    }

    inline auto xregistry::find(xeus::xguid id) -> typename storage_type::mapped_type&
    {
        auto it = m_storage.find(id);
        if (it == m_storage.end())
        {
            throw std::runtime_error("Could not find specified id in transport registry");
        }
        return it->second;
    }

    /*******************
     * xmaker template *
     *******************/

    template <template <class> class CRTP, class... P>
    void xmaker(xeus::xcomm&& comm, const xeus::xjson& state)
    {
        auto model = xgenerator<CRTP, P...>(std::move(comm), true);
        model.apply_patch(state);
        get_transport_registry().register_owning(reinterpret_cast<xmaterialize<CRTP, P...>&&>(model));
    }
}
#endif
