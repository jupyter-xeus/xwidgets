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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        template <class O, class T>
        xdropdown(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using dropdown = xmaterialize<xdropdown>;

    using dropdown_generator = xgenerator<xdropdown>;

    /****************************
     * xdropdown implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xdropdown<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xdropdown<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "DropdownModel";
        this->_view_name() = "DropdownView";
    }
}
#endif
