/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_MIXIN_NUMERIC_HPP
#define XWIDGETS_MIXIN_NUMERIC_HPP

#include <nlohmann/json.hpp>
#include <xeus/xmessage.hpp>
#include <xproperty/xobserved.hpp>

#include "xcommon.hpp"

namespace xw
{
    namespace nl = nlohmann;

    template <class D>
    struct xnumber_traits;

    namespace mixin
    {

        /************************
         * xnumeric declaration *
         ************************/

        template <class D>
        class xnumeric
        {
        public:

            using derived_type = D;
            using value_type = typename xnumber_traits<derived_type>::value_type;

            void serialize_state(nl::json&, xeus::buffer_sequence&) const;
            void apply_patch(const nl::json&, const xeus::buffer_sequence&);

            XPROPERTY(value_type, derived_type, value);

        protected:

            xnumeric() = default;
        };

        /********************************
         * xnumeric_bounded declaration *
         ********************************/

        template <class D>
        class xnumeric_bounded : public xnumeric<D>
        {
        public:

            using base_type = xnumeric<D>;
            using derived_type = D;
            using typename base_type::value_type;

            void serialize_state(nl::json&, xeus::buffer_sequence&) const;
            void apply_patch(const nl::json&, const xeus::buffer_sequence&);

            XPROPERTY(value_type, derived_type, max, value_type(100));
            XPROPERTY(value_type, derived_type, min);

        protected:

            xnumeric_bounded();

        private:

            void setup_properties();
        };

        /***************************
         * xnumeric implementation *
         ***************************/

        template <class D>
        inline void xnumeric<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
        {
            xwidgets_serialize(value(), state["value"], buffers);
        }

        /***********************************
         * xnumeric_bounded implementation *
         ***********************************/

        template <class D>
        inline void xnumeric_bounded<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
        {
            base_type::serialize_state(state, buffers);

            xwidgets_serialize(max(), state["max"], buffers);
            xwidgets_serialize(min(), state["min"], buffers);
        }

        template <class D>
        inline xnumeric_bounded<D>::xnumeric_bounded()
        {
            setup_properties();
        }

        template <class D>
        inline void xnumeric_bounded<D>::setup_properties()
        {
            static_cast<derived_type*>(this)->template validate<derived_type, value_type>(
                "value",
                [](auto& owner, auto& proposal)
                {
                    if (proposal > owner.max())
                    {
                        proposal = owner.max();
                    }
                    if (proposal < owner.min())
                    {
                        proposal = owner.min();
                    }
                }
            );

            static_cast<derived_type*>(this)->template validate<derived_type, value_type>(
                "min",
                [](auto& owner, auto& proposal)
                {
                    if (proposal > owner.max())
                    {
                        throw std::runtime_error("setting min > max");
                    }
                    if (proposal > owner.value())
                    {
                        owner.value = proposal;
                    }
                }
            );

            static_cast<derived_type*>(this)->template validate<derived_type, value_type>(
                "max",
                [](auto& owner, auto& proposal)
                {
                    if (proposal < owner.min())
                    {
                        throw std::runtime_error("setting max < min");
                    }
                    if (proposal < owner.value())
                    {
                        owner.value = proposal;
                    }
                }
            );
        }
    }
}

#endif
