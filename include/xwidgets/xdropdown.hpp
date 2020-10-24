/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_DROPDOWN_HPP
#define XWIDGETS_DROPDOWN_HPP

#include <utility>

#include "xmaterialize.hpp"
#include "xselection.hpp"

namespace xw
{
    /************************
     * dropdown declaration *
     ************************/

    template <class D>
    class xdropdown : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xdropdown();

        template <class O, class T>
        xdropdown(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using dropdown = xmaterialize<xdropdown>;

    /****************************
     * xdropdown implementation *
     ****************************/

    template <class D>
    inline void xdropdown<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xdropdown<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xdropdown<D>::xdropdown()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class O, class T>
    inline xdropdown<D>::xdropdown(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xdropdown<D>::set_defaults()
    {
        this->_model_name() = "DropdownModel";
        this->_view_name() = "DropdownView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xdropdown>;
    extern template class xtransport<xmaterialize<xdropdown>>;
}
#endif
