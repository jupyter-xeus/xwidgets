#ifndef XWIDGETS_HOLDER_ID_HPP
#define XWIDGETS_HOLDER_ID_HPP

#include <utility>

#include "xtl/xany.hpp"
#include "xtl/xclosure.hpp"

#include "xholder.hpp"
#include "xregistry.hpp"

namespace xw
{
    template <template <class> class CRTP>
    xholder<CRTP> make_id_holder(xeus::xguid id);

    namespace detail
    {
        template <template <class> class CRTP>
        class xholder_id : public xholder_impl<CRTP>
        {
        public:

            using base_type = xholder_impl<CRTP>;

            xholder_id(xeus::xguid id)
                : base_type(),
                  m_id(id)
            {
            }

            virtual ~xholder_id() = default;

            virtual base_type* clone() const override
            {
                return new xholder_id(*this);
            }

            virtual void display() const override
            {
                auto& holder = get_transport_registry().find(m_id);
                holder.display();
            }

            virtual xeus::xguid id() const override
            {
                auto& holder = get_transport_registry().find(m_id);
                return holder.id();
            }

            virtual xtl::any value() & override
            {
                auto& holder = get_transport_registry().find(m_id);
                return holder.value();
            }

            virtual const xtl::any value() const & override
            {
                const auto& holder = get_transport_registry().find(m_id);
                return holder.value();
            }

        private:

            xholder_id(const xholder_id&) = default;
            xholder_id(xholder_id&&) = default;
            xeus::xguid m_id;
        };
    }

    template <template <class> class CRTP>
    xholder<CRTP> make_id_holder(xeus::xguid id)
    {
        return xholder<CRTP>(new detail::xholder_id<CRTP>(id));
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>::xholder(const CRTP<D>& rhs)
        : xholder(make_id_holder<CRTP>(rhs.id()))
    {
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>& xholder<CRTP>::operator=(const CRTP<D>& rhs)
    {
        using std::swap;
        xholder<CRTP> tmp(make_id_holder<CRTP>(rhs.id()));
        swap(tmp, *this);
        return *this;
    }

    template <template <class> class CRTP>
    void from_json(const xeus::xjson& j, xholder<CRTP>& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        o = make_id_holder<CRTP>(guid);
    }
}
#endif
