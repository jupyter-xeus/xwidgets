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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xlabel<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xlabel<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
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

#ifndef _WIN32
    extern template class xmaterialize<xlabel>;
    extern template xmaterialize<xlabel>::xmaterialize();
    extern template class xtransport<xmaterialize<xlabel>>;
    extern template class xgenerator<xlabel>;
    extern template xgenerator<xlabel>::xgenerator();
    extern template class xtransport<xgenerator<xlabel>>;
#endif
}

#endif
