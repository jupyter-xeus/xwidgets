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
     *****************************/

    template <class D>
    class xprogress_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<html_color>, derived_type, bar_color);

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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(std::string, derived_type, bar_style, "", XEITHER("success", "info", "warning", "danger", ""));
        XPROPERTY(::xw::progress_style, derived_type, style);

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
    inline xeus::xjson xprogress_style<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(description_width, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bar_color, state);

        return state;
    }

    template <class D>
    inline void xprogress_style<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(description_width, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bar_color, patch);
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "ProgressStyleModel";
    }

    /****************************
     * xprogress implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xprogress<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bar_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    template <class D>
    inline void xprogress<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bar_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch);
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

    XWIDGETS_EXTERN template class xmaterialize<xprogress_style>;
    XWIDGETS_EXTERN template xmaterialize<xprogress_style>::xmaterialize();
    XWIDGETS_EXTERN template class xtransport<xmaterialize<xprogress_style>>;
    XWIDGETS_EXTERN template class xgenerator<xprogress_style>;
    XWIDGETS_EXTERN template xgenerator<xprogress_style>::xgenerator();
    XWIDGETS_EXTERN template class xtransport<xgenerator<xprogress_style>>;

    XWIDGETS_EXTERN template class XWIDGETS_API xmaterialize<xprogress, int>;
    XWIDGETS_EXTERN template xmaterialize<xprogress, int>::xmaterialize();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xmaterialize<xprogress, int>>;
    XWIDGETS_EXTERN template class XWIDGETS_API xgenerator<xprogress, int>;
    XWIDGETS_EXTERN template xgenerator<xprogress, int>::xgenerator();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xgenerator<xprogress, int>>;

    XWIDGETS_EXTERN template class XWIDGETS_API xmaterialize<xprogress, float>;
    XWIDGETS_EXTERN template xmaterialize<xprogress, float>::xmaterialize();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xmaterialize<xprogress, float>>;
    XWIDGETS_EXTERN template class XWIDGETS_API xgenerator<xprogress, float>;
    XWIDGETS_EXTERN template xgenerator<xprogress, float>::xgenerator();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xgenerator<xprogress, float>>;

    XWIDGETS_EXTERN template class XWIDGETS_API xmaterialize<xprogress, double>;
    XWIDGETS_EXTERN template xmaterialize<xprogress, double>::xmaterialize();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xmaterialize<xprogress, double>>;
    XWIDGETS_EXTERN template class XWIDGETS_API xgenerator<xprogress, double>;
    XWIDGETS_EXTERN template xgenerator<xprogress, double>::xgenerator();
    XWIDGETS_EXTERN template class XWIDGETS_API xtransport<xgenerator<xprogress, double>>;
}

#endif
