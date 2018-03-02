/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_LABEL_HPP
#define XWIDGETS_LABEL_HPP

#include "xmaterialize.hpp"
#include "xstring.hpp"

namespace xw
{
    /*********************
     * label declaration *
     *********************/

    template <class D>
    class xlabel : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        xlabel();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using label = xmaterialize<xlabel>;

    using label_generator = xgenerator<xlabel>;

    /*************************
     * xlabel implementation *
     *************************/

    template <class D>
    inline xeus::xjson xlabel<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        return state;
    }

    template <class D>
    inline void xlabel<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xlabel<D>::xlabel()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlabel<D>::set_defaults()
    {
        this->_model_name() = "HTMLModel";
        this->_view_name() = "HTMLView";
    }

    /*********************
     * precompiled types *
     *********************/

    XWIDGETS_EXTERN template class XWIDGETS_API xmaterialize<xlabel>;
    XWIDGETS_EXTERN template xmaterialize<xlabel>::xmaterialize();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xmaterialize<xlabel>>;
    XWIDGETS_EXTERN template class XWIDGETS_API xgenerator<xlabel>;
    XWIDGETS_EXTERN template xgenerator<xlabel>::xgenerator();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xgenerator<xlabel>>;
}

#endif
