#ifndef XWIDGETS_HOLDER_ID_HPP
#define XWIDGETS_HOLDER_ID_HPP

#include "xwidgets/xholder.hpp"
#include "xwidgets/xregistry.hpp"

namespace xw
{
    /*****************************
     * xholder_id implementation *
     *****************************/

    namespace detail
    {
        class xholder_id : public xholder_impl
        {
        public:

            using base_type = xholder_impl;

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

    xholder make_id_holder(xeus::xguid id)
    {
        return xholder(new detail::xholder_id(id));
    }
}

#endif
