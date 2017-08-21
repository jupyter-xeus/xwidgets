/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_HTML_HPP
#define XWIDGETS_HTML_HPP

#include "xstring.hpp"

namespace xeus
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

        xhtml();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

    private:

        void set_defaults();
    };

    class html final : public xhtml<html>
    {
    public:

        using base_type = xhtml<html>;

        html()
            : base_type()
        {
            this->open();
        }

        ~html()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        html(const html& other)
            : base_type(other)
        {
            this->open();
        }

        html& operator=(const html& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /************************
     * xhtml implementation *
     ************************/

    template <class D>
    inline xhtml<D>::xhtml()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xhtml<D>::get_state() const
    {
        xjson state = base_type::get_state();
        return state;
    }

    template <class D>
    inline void xhtml<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline void xhtml<D>::set_defaults()
    {
        this->_model_name() = "HTMLModel";
        this->_view_name() = "HTMLView";
    }
}

#endif
