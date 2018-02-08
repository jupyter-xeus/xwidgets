/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_ACCORDION_HPP
#define XWIDGETS_ACCORDION_HPP

#include "xmaterialize.hpp"
#include "xselection_container.hpp"

namespace xw
{
    /*************************
     * accordion declaration *
     *************************/

    template <class D>
    class xaccordion : public xselection_container<D>
    {
    public:

        using base_type = xselection_container<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        xaccordion();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using accordion = xmaterialize<xaccordion>;

    using accordion_generator = xgenerator<xaccordion>;

    /*****************************
     * xaccordion implementation *
     *****************************/

    template <class D>
    inline xeus::xjson xaccordion<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xaccordion<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xaccordion<D>::xaccordion()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xaccordion<D>::set_defaults()
    {
        this->_model_name() = "AccordionModel";
        this->_view_name() = "AccordionView";
    }

    /*********************
     * precompiled types *
     *********************/

    XWIDGETS_EXTERN template class XWIDGETS_API xmaterialize<xaccordion>;
    XWIDGETS_EXTERN template xmaterialize<xaccordion>::xmaterialize();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xmaterialize<xaccordion>>;
    XWIDGETS_EXTERN template class XWIDGETS_API xgenerator<xaccordion>;
    XWIDGETS_EXTERN template xgenerator<xaccordion>::xgenerator();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xgenerator<xaccordion>>;
}

#endif
