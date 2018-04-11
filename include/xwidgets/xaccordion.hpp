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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xaccordion<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xaccordion<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
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

#ifndef _WIN32
    extern template class xmaterialize<xaccordion>;
    extern template xmaterialize<xaccordion>::xmaterialize();
    extern template class xtransport<xmaterialize<xaccordion>>;
    extern template class xgenerator<xaccordion>;
    extern template xgenerator<xaccordion>::xgenerator();
    extern template class xtransport<xgenerator<xaccordion>>;
#endif
}

#endif
