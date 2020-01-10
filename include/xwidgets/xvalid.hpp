/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_VALID_HPP
#define XWIDGETS_VALID_HPP

#include <string>

#include "xboolean.hpp"
#include "xmaterialize.hpp"

namespace xw
{
    /*********************
     * valid declaration *
     *********************/

    template <class D>
    class xvalid : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, readout, "Invalid");

    protected:

        xvalid();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using valid = xmaterialize<xvalid>;

    /*************************
     * xvalid implementation *
     *************************/

    template <class D>
    inline void xvalid<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(readout(), state["readout"], buffers);
    }

    template <class D>
    inline void xvalid<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(readout, patch, buffers);
    }

    template <class D>
    inline xvalid<D>::xvalid()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvalid<D>::set_defaults()
    {
        this->_model_name() = "ValidModel";
        this->_view_name() = "ValidView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xvalid>;
    extern template xmaterialize<xvalid>::xmaterialize();
    extern template class xtransport<xmaterialize<xvalid>>;
#endif
}
#endif
