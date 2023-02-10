/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

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
                : base_type()
                , m_id(id)
            {
            }

            ~xholder_id() override = default;

            base_type* clone() const override
            {
                return new xholder_id(*this);
            }

            void display() const override
            {
                return get_transport_registry().find(m_id).display();
            }

            xeus::xguid id() const override
            {
                return get_transport_registry().find(m_id).id();
            }

            void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const override
            {
                return get_transport_registry().find(m_id).serialize_state(state, buffers);
            }

            const std::vector<xjson_path_type>& buffer_paths() const override
            {
                return get_transport_registry().find(m_id).buffer_paths();
            }

            xtl::any value() & override
            {
                return get_transport_registry().find(m_id).value();
            }

            const xtl::any value() const& override
            {
                return get_transport_registry().find(m_id).value();
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
