/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_NUMBER_IMPL_HPP
#define XWIDGETS_NUMBER_IMPL_HPP

#include "xwidget.hpp"

namespace xw
{
    /***********************
     * numeral declaration *
     ***********************/

    template <class D>
    struct xnumber_traits;

    template <class D>
    class xnumber_impl : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;
        using value_type = typename xnumber_traits<derived_type>::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, value);

    protected:

        xnumber_impl() = default;
    };

    template <class D>
    class xbounded_number_impl : public xnumber_impl<D>
    {
    public:

        using base_type = xnumber_impl<D>;
        using derived_type = D;
        using value_type = typename base_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, max, value_type(100));
        XPROPERTY(value_type, derived_type, min);

    protected:

        xbounded_number_impl();

    private:

        void setup_properties();
    };

    /*********************************
     *  xnumber_impl implementation  *
     *********************************/

    template <class D>
    inline void xnumber_impl<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(value(), state["value"], buffers);
    }

    template <class D>
    inline void xnumber_impl<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(value, patch, buffers);
    }

    /*****************************************
     *  xbounded_number_impl implementation  *
     *****************************************/

    template <class D>
    inline void xbounded_number_impl<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(max(), state["max"], buffers);
        xwidgets_serialize(min(), state["min"], buffers);
    }

    template <class D>
    inline void
    xbounded_number_impl<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(min, patch, buffers);
    }

    template <class D>
    inline xbounded_number_impl<D>::xbounded_number_impl()
        : base_type()
    {
        setup_properties();
    }

    template <class D>
    inline void xbounded_number_impl<D>::setup_properties()
    {
        this->template validate<value_type>(
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

        this->template validate<value_type>(
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

        this->template validate<value_type>(
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

#endif
