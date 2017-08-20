#ifndef XWIDGETS_HOLDER_ID_HPP
#define XWIDGETS_HOLDER_ID_HPP

#include <utility>

#include "xholder.hpp"
#include "xregistry.hpp"  

namespace xeus
{
    template <class D>
    xholder make_id_holder(const xtransport<D>& value);

    namespace detail
    {
        template <class D>
        class xholder_id : public xholder_impl
        {
        public:

            using base_type = xholder_impl;

            xholder_id(const xtransport<D>& value)
                : base_type(),
                  m_id(value.id())
            {
            }
        
            virtual ~xholder_id() = default;

            virtual xholder_impl* clone() const override
            {
                return new xholder_id(*this);
            }

            virtual void display() const override
            {
                auto holder = get_transport_registry().find(m_id);
                holder.display();
            }
        
            virtual xguid id() const override
            {
                return m_id;
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
            xguid m_id;
        };
    }

    template <class D>
    xholder make_id_holder(const xtransport<D>& value)
    {
        return xholder(new detail::xholder_id<D>(value));
    }

    template <class D>
    xholder& xholder::operator=(const xtransport<D>& rhs)
    {
        using std::swap;
        xholder tmp(make_id_holder(rhs));
        swap(tmp, *this);
        return *this;
    }
}
#endif

