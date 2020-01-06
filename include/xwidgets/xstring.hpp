/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_STRING_HPP
#define XWIDGETS_STRING_HPP

#include <string>

#include "xwidget.hpp"
#include "xtrait.hpp"

namespace xw
{
    /****************************
     * base xstring declaration *
     ****************************/

    template <class D>
    class xstring : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::string, derived_type, description);
        XTRAIT(std::string, derived_type, value);
        XTRAIT(std::string, derived_type, placeholder, "\u00A0");

    protected:

        xstring();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /**************************
     * xstring implementation *
     **************************/

    template <class D>
    inline void xstring<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(value, state, buffers);
        set_patch_from_property(placeholder, state, buffers);
    }

    template <class D>
    inline void xstring<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(value, patch, buffers);
        set_property_from_patch(placeholder, patch, buffers);
    }

    template <class D>
    inline xstring<D>::xstring()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xstring<D>::set_defaults()
    {
        this->_model_name() = "StringModel";
        this->_view_name() = "";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }
}

#endif
