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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xselect<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(rows, state, buffers);
    }

    template <class D>
    inline void xselect<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(rows, patch, buffers);
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
        this->_model_name() = "SelectModel";
        this->_view_name() = "SelectView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /***********************************
     * xselect_multiple implementation *
     ***********************************/

    template <class D>
    inline void xselect_multiple<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(rows, state, buffers);
    }

    template <class D>
    inline void xselect_multiple<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(rows, patch, buffers);
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
        this->_model_name() = "SelectMultipleModel";
        this->_view_name() = "SelectMultipleView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xselect>;
    extern template xmaterialize<xselect>::xmaterialize();
    extern template class xtransport<xmaterialize<xselect>>;
    extern template class xgenerator<xselect>;
    extern template xgenerator<xselect>::xgenerator();
    extern template class xtransport<xgenerator<xselect>>;

    extern template class xmaterialize<xselect_multiple>;
    extern template xmaterialize<xselect_multiple>::xmaterialize();
    extern template class xtransport<xmaterialize<xselect_multiple>>;
    extern template class xgenerator<xselect_multiple>;
    extern template xgenerator<xselect_multiple>::xgenerator();
    extern template class xtransport<xgenerator<xselect_multiple>>;
#endif
}
#endif
