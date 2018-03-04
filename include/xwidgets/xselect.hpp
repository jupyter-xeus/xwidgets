/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_SELECT_HPP
#define XWIDGETS_SELECT_HPP

#include "xmaterialize.hpp"
#include "xprecompiled_macros.hpp"
#include "xselection.hpp"

namespace xw
{
    /**********************
     * select declaration *
     **********************/

    template <class D>
    class xselect : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(int, derived_type, rows, 5);

    protected:

        xselect();

        template <class O, class T>
        xselect(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using select = xmaterialize<xselect>;

    using select_generator = xgenerator<xselect>;

    /*******************************
     * select_multiple declaration *
     *******************************/

    template <class D>
    class xselect_multiple : public xmultiple_selection<D>
    {
    public:

        using base_type = xmultiple_selection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(int, derived_type, rows, 5);

    protected:

        xselect_multiple();
        xselect_multiple(options_type&& options);
        xselect_multiple(const options_type& options);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using select_multiple = xmaterialize<xselect_multiple>;

    using select_multiple_generator = xgenerator<xselect_multiple>;

    /**************************
     * xselect implementation *
     **************************/

    template <class D>
    inline xeus::xjson xselect<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(rows, state);

        return state;
    }

    template <class D>
    inline void xselect<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(rows, patch);
    }

    template <class D>
    inline xselect<D>::xselect()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class O, class T>
    inline xselect<D>::xselect(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xselect<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SelectModel";
        this->_view_name() = "SelectView";
    }

    /***********************************
     * xselect_multiple implementation *
     ***********************************/

    template <class D>
    inline xeus::xjson xselect_multiple<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(rows, state);

        return state;
    }

    template <class D>
    inline void xselect_multiple<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(rows, patch);
    }

    template <class D>
    inline xselect_multiple<D>::xselect_multiple()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xselect_multiple<D>::xselect_multiple(options_type&& options)
        : base_type(std::move(options))
    {
        set_defaults();
    }

    template <class D>
    inline xselect_multiple<D>::xselect_multiple(const options_type& options)
        : base_type(options)
    {
        set_defaults();
    }

    template <class D>
    inline void xselect_multiple<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SelectMultipleModel";
        this->_view_name() = "SelectMultipleView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    XPRECOMPILE(EXTERN, (xselect, xselect_multiple));
#endif
}
#endif
