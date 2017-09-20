#ifndef XWIDGETS_HOLDER_ID_HPP
#define XWIDGETS_HOLDER_ID_HPP

#include <utility>

#include "xholder.hpp"
#include "xregistry.hpp"

namespace xw
{
    template <template <class> class CRTP, class D>
    xholder<CRTP> make_id_holder(const CRTP<D>& value);

    namespace detail
    {
        template <template <class> class CRTP, class D>
        class xholder_id : public xholder_impl<CRTP>
        {
        public:

            using base_type = xholder_impl<CRTP>;

            xholder_id(const CRTP<D>& value)
                : base_type(),
                  m_id(value.id())
            {
            }

            virtual ~xholder_id() = default;

            virtual base_type* clone() const override
            {
                return new xholder_id(*this);
            }

            virtual void display() const override
            {
                auto holder = get_transport_registry().find(m_id);
                holder.display();
            }

            virtual xeus::xguid id() const override
            {
                return m_id;
            }

            virtual bool owning() const override
            {
                return false;
            }

            inline D& value() & noexcept
            {
                auto holder = get_transport_registry().find(m_id);
                return holder.template get<D>();
            }

            inline const D& value() const & noexcept
            {
                auto holder = get_transport_registry().find(m_id);
                return holder.template get<D>();
            }

            inline D value() && noexcept
            {
                auto holder = get_transport_registry().find(m_id);
                return holder.template get<D>();
            }

        private:

            xholder_id(const xholder_id&) = default;
            xeus::xguid m_id;
        };
    }

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_id_holder(const CRTP<D>& value)
    {
        return xholder<CRTP>(new detail::xholder_id<CRTP, D>(value));
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>::xholder(const CRTP<D>& rhs)
        : xholder(make_id_holder<CRTP>(rhs))
    {
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>& xholder<CRTP>::operator=(const CRTP<D>& rhs)
    {
        using std::swap;
        xholder<CRTP> tmp(make_id_holder<CRTP>(rhs));
        swap(tmp, *this);
        return *this;
    }
}
#endif
