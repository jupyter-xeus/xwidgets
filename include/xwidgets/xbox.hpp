/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BOX_HPP
#define XWIDGETS_BOX_HPP

#include "xholder_id.hpp"
#include "xmaterialize.hpp"
#include "xwidget.hpp"

namespace xw
{
    /********************
     * xbox declaration *
     ********************/

    // TODO: use xholder<xwidget> instead of xholder<xtransport>
    using xbox_children_list_type = std::vector<xholder<xtransport>>;

    template <class D>
    class xbox : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;
        using children_list_type = xbox_children_list_type;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(X_CASELESS_STR_ENUM(success, info, warning, danger,), derived_type, box_style);
        XPROPERTY(children_list_type, derived_type, children);

        template <class T>
        void add(const xtransport<T>& w);

        template <class T>
        void add(xtransport<T>&& w);

    protected:

        xbox();

    private:

        void set_defaults();
    };

    /********************
     * hbox declaration *
     ********************/

    template <class D>
    class xhbox : public xbox<D>
    {
    public:

        using base_type = xbox<D>;
        using derived_type = D;

    protected:

        xhbox();

    private:

        void set_defaults();
    };

    using hbox = xmaterialize<xhbox>;

    using hbox_generator = xgenerator<xhbox>;

    /********************
     * vbox declaration *
     ********************/

    template <class D>
    class xvbox : public xbox<D>
    {
    public:

        using base_type = xbox<D>;
        using derived_type = D;

    protected:

        xvbox();

    private:

        void set_defaults();
    };

    using vbox = xmaterialize<xvbox>;

    using vbox_generator = xgenerator<xvbox>;

    /***********************
     * xbox implementation *
     ***********************/

    template <class D>
    inline xeus::xjson xbox<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(box_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(children, state);

        return state;
    }

    template <class D>
    inline void xbox<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(box_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(children, patch);
    }

    template <class D>
    template <class T>
    inline void xbox<D>::add(const xtransport<T>& w)
    {
        this->children().emplace_back(make_id_holder(w));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(children, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    template <class T>
    inline void xbox<D>::add(xtransport<T>&& w)
    {
        this->children().emplace_back(make_owning_holder(std::move(w)));
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(children, state);
        this->send_patch(std::move(state));
    }

    template <class D>
    inline xbox<D>::xbox()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xbox<D>::set_defaults()
    {
        this->_model_name() = "BoxModel";
        this->_view_name() = "BoxView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
    }

    /************************
     * xhbox implementation *
     ************************/

    template <class D>
    inline xhbox<D>::xhbox()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xhbox<D>::set_defaults()
    {
        this->_model_name() = "HBoxModel";
        this->_view_name() = "HBoxView";
    }

    /************************
     * xvbox implementation *
     ************************/

    template <class D>
    inline xvbox<D>::xvbox()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvbox<D>::set_defaults()
    {
        this->_model_name() = "VBoxModel";
        this->_view_name() = "VBoxView";
    }
}

#endif
