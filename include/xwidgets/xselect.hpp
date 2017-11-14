/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_SELECT_HPP
#define XWIDGETS_SELECT_HPP

#include "xmaterialize.hpp"
#include "xselection.hpp"

namespace xw
{
    /**********************
     * select declaration *
     **********************/

    template <class D>
    class xselect : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(int, derived_type, rows, 5);

    protected:

        template <class O, class T>
        xselect(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using select = xmaterialize<xselect>;

    using select_generator = xgenerator<xselect>;

    /**************************
     * xselect implementation *
     **************************/

    template <class D>
    inline xeus::xjson xselect<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(rows, state);

        return state;
    }

    template <class D>
    inline void xselect<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(rows, patch)
    }

    template <class D>
    template <class O, class T>
    inline xselect<D>::xselect(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xselect<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SelectModel";
        this->_view_name() = "SelectView";
    }
}
#endif
