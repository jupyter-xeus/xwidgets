/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_HTML_HPP
#define XWIDGETS_HTML_HPP

#include "xmaterialize.hpp"
#include "xstring.hpp"

namespace xw
{
    /********************
     * html declaration *
     ********************/

    template <class D>
    class xhtml : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xhtml();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using html = xmaterialize<xhtml>;

    /************************
     * xhtml implementation *
     ************************/

    template <class D>
    inline void xhtml<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xhtml<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xhtml<D>::xhtml()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xhtml<D>::set_defaults()
    {
        this->_model_name() = "HTMLModel";
        this->_view_name() = "HTMLView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xhtml>;
    extern template xmaterialize<xhtml>::xmaterialize();
    extern template class xtransport<xmaterialize<xhtml>>;
#endif
}

#endif
