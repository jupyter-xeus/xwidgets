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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

    protected:

        xhtml();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using html = xmaterialize<xhtml>;

    using html_generator = xgenerator<xhtml>;

    /************************
     * xhtml implementation *
     ************************/

    template <class D>
    inline xeus::xjson xhtml<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xhtml<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
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
    extern template class xgenerator<xhtml>;
    extern template xgenerator<xhtml>::xgenerator();
    extern template class xtransport<xgenerator<xhtml>>;
#endif
}

#endif
