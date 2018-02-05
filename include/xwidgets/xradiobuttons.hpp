/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_RADIOBUTTONS_HPP
#define XWIDGETS_RADIOBUTTONS_HPP

#include <utility>

#include "xmaterialize.hpp"
#include "xselection.hpp"

namespace xw
{
    /****************************
     * radiobuttons declaration *
     ****************************/

    template <class D>
    class xradiobuttons : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        template <class O, class T>
        xradiobuttons(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using radiobuttons = xmaterialize<xradiobuttons>;

    using radiobuttons_generator = xgenerator<xradiobuttons>;

    /********************************
     * xradiobuttons implementation *
     ********************************/

    template <class D>
    inline xeus::xjson xradiobuttons<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xradiobuttons<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    template <class O, class T>
    inline xradiobuttons<D>::xradiobuttons(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xradiobuttons<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "RadioButtonsModel";
        this->_view_name() = "RadioButtonsView";
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xradiobuttons>;
    extern template xmaterialize<xradiobuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xradiobuttons>>;
    extern template class xgenerator<xradiobuttons>;
    extern template xgenerator<xradiobuttons>::xgenerator();
    extern template class xtransport<xgenerator<xradiobuttons>>;
}
#endif
