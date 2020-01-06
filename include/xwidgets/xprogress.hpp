/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_PROGRESS_HPP
#define XWIDGETS_PROGRESS_HPP

#include <string>

#include "xtl/xoptional.hpp"

#include "xcolor.hpp"
#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xnumber.hpp"
#include "xstyle.hpp"

namespace xw
{
    /******************************
     * progress_style declaration *
     ******************************/

    template <class D>
    class xprogress_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::string, derived_type, description_width);
        XTRAIT(xtl::xoptional<html_color>, derived_type, bar_color);

    protected:

        xprogress_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using progress_style = xmaterialize<xprogress_style>;

    using progress_style_generator = xgenerator<xprogress_style>;

    /***********************
     * progress declaration *
     ***********************/

    template <class D>
    class xprogress : public xnumber<D>
    {
    public:

        using base_type = xnumber<D>;
        using derived_type = D;

        using value_type = typename base_type::value_type;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XTRAIT(std::string, derived_type, bar_style, "", XEITHER("success", "info", "warning", "danger", ""));
        XTRAIT(::xw::progress_style, derived_type, style);

    protected:

        xprogress();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T>
    using progress = xmaterialize<xprogress, T>;

    template <class T>
    using progress_generator = xgenerator<xprogress, T>;

    template <class T>
    struct xnumber_traits<progress<T>>
    {
        using value_type = T;
    };

    template <class T>
    struct xnumber_traits<progress_generator<T>>
    {
        using value_type = T;
    };

    /**********************************
     * xprogress_style implementation *
     **********************************/

    template <class D>
    inline void xprogress_style<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(description_width, state, buffers);
        set_patch_from_property(bar_color, state, buffers);
    }

    template <class D>
    inline void xprogress_style<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(bar_color, patch, buffers);
    }

    template <class D>
    inline xprogress_style<D>::xprogress_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xprogress_style<D>::set_defaults()
    {
        this->_model_name() = "ProgressStyleModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /****************************
     * xprogress implementation *
     ****************************/

    template <class D>
    inline void xprogress<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(orientation, state, buffers);
        set_patch_from_property(bar_style, state, buffers);
        set_patch_from_property(style, state, buffers);
    }

    template <class D>
    inline void xprogress<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(bar_style, patch, buffers);
        set_property_from_patch(style, patch, buffers);
    }

    template <class D>
    inline xprogress<D>::xprogress()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xprogress<D>::set_defaults()
    {
        this->_model_name() = "FloatProgressModel";
        this->_view_name() = "ProgressView";
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xprogress_style>;
    extern template xmaterialize<xprogress_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress_style>>;
    extern template class xgenerator<xprogress_style>;
    extern template xgenerator<xprogress_style>::xgenerator();
    extern template class xtransport<xgenerator<xprogress_style>>;

    extern template class xmaterialize<xprogress, int>;
    extern template xmaterialize<xprogress, int>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, int>>;
    extern template class xgenerator<xprogress, int>;
    extern template xgenerator<xprogress, int>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, int>>;

    extern template class xmaterialize<xprogress, float>;
    extern template xmaterialize<xprogress, float>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, float>>;
    extern template class xgenerator<xprogress, float>;
    extern template xgenerator<xprogress, float>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, float>>;

    extern template class xmaterialize<xprogress, double>;
    extern template xmaterialize<xprogress, double>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, double>>;
    extern template class xgenerator<xprogress, double>;
    extern template xgenerator<xprogress, double>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, double>>;
#endif
}

#endif
