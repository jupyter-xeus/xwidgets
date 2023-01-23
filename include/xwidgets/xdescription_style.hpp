/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_DESCRIPTION_HPP
#define XWIDGETS_DESCRIPTION_HPP

#include <string>

#include "xstyle.hpp"

namespace xw
{
    /*********************************
     * description_style declaration *
     *********************************/

    template <class D>
    class xdescription_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, description_width);

    protected:

        xdescription_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using description_style = xmaterialize<xdescription_style>;

    /********************************
     * xdescription_style implementation *
     ********************************/

    template <class D>
    inline void xdescription_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(description_width(), state["description_width"], buffers);
    }

    template <class D>
    inline void xdescription_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description_width, patch, buffers);
    }

    template <class D>
    inline xdescription_style<D>::xdescription_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xdescription_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "DescriptionStyleModel";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xdescription_style>;
    extern template class xtransport<xmaterialize<xdescription_style>>;

}
#endif
