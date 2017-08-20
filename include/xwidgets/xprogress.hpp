/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_PROGRESS_HPP
#define XWIDGETS_PROGRESS_HPP

#include "xstyle.hpp"
#include "xnumber.hpp"

namespace xeus
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

        xprogress_style();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(std::string), D, bar_color);

    private:

        void set_defaults();
    };

    class progress_style final : public xprogress_style<progress_style>
    {
    public:

        using base_type = xprogress_style<progress_style>;

        progress_style() : base_type()
        {
            this->open();
        }

        ~progress_style()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        progress_style(const progress_style& other) : base_type(other)
        {
            this->open();
        }

        progress_style& operator=(const progress_style& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

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

        xprogress();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(X_CASELESS_STR_ENUM(horizontal, vertical), derived_type, orientation, "horizontal");
        XPROPERTY(X_CASELESS_STR_ENUM(success, info, warning, danger,), derived_type, bar_style);
        XPROPERTY(::xeus::progress_style, derived_type, style);

    private:

        void set_defaults();
    };

    template <class T>
    class progress final : public xprogress<progress<T>>
    {
    public:

        using base_type = xprogress<progress<T>>;

        progress() : base_type()
        {
            this->open();
        }

        ~progress()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        progress(const progress& other) : base_type(other)
        {
            this->open();
        }

        progress& operator=(const progress& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    template <class T> 
    struct xnumber_traits<progress<T>>
    {
        using value_type = T;
    };

    /**********************************
     * xprogress_style implementation *
     **********************************/

    template <class D>
    inline xprogress_style<D>::xprogress_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xprogress_style<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(bar_color, state);

        return state;
    }

    template <class D>
    inline void xprogress_style<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(bar_color, patch);
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
    inline xprogress<D>::xprogress()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xprogress<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(bar_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(style, state);

        return state;
    }

    template <class D>
    inline void xprogress<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(bar_style, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(style, patch)
    }

    template <class D>
    inline void xprogress<D>::set_defaults()
    {
        this->_model_name() = "FloatProgressModel";
        this->_view_name() = "ProgressView";
    }
}

#endif
