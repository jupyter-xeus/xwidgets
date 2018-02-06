/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TAB_HPP
#define XWIDGETS_TAB_HPP

#include "xmaterialize.hpp"
#include "xselection_container.hpp"

namespace xw
{
    /*************************
     * accordion declaration *
     *************************/

    template <class D>
    class xtab : public xselection_container<D>
    {
    public:

        using base_type = xselection_container<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        xtab();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using tab = xmaterialize<xtab>;

    using tab_generator = xgenerator<xtab>;

    /***********************
     * xtab implementation *
     ***********************/

    template <class D>
    inline xeus::xjson xtab<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xtab<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xtab<D>::xtab()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtab<D>::set_defaults()
    {
        this->_model_name() = "TabModel";
        this->_view_name() = "TabView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xtab>;
    extern template xmaterialize<xtab>::xmaterialize();
    extern template class xtransport<xmaterialize<xtab>>;
    extern template class xgenerator<xtab>;
    extern template xgenerator<xtab>::xgenerator();
    extern template class xtransport<xgenerator<xtab>>;
#endif
}

#endif
