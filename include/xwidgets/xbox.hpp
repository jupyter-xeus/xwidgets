/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BOX_HPP
#define XWIDGETS_BOX_HPP

#include <utility>
#include <vector>

#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xwidget.hpp"

namespace xw
{
    /********************
     * xbox declaration *
     ********************/

    template <class D>
    class xbox : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;
        using children_list_type = std::vector<xholder>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, box_style, "", XEITHER("success", "info", "warning", "danger", ""));

        XPROPERTY(children_list_type, derived_type, children);

        template <class T>
        void add(const xtransport<T>& w);

        template <class T>
        void add(xtransport<T>&& w);

        template <class T>
        enable_xtransport_t<T> add(std::shared_ptr<T> w);

        template <class T>
        void remove(const xtransport<T>& w);

        void clear();

    protected:

        xbox();
        using base_type::base_type;

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

    /***********************
     * xbox implementation *
     ***********************/

    template <class D>
    inline void xbox<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(box_style(), state["box_style"], buffers);
        xwidgets_serialize(children(), state["children"], buffers);
    }

    template <class D>
    inline void xbox<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(box_style, patch, buffers);
        set_property_from_patch(children, patch, buffers);
    }

    template <class D>
    template <class T>
    inline void xbox<D>::add(const xtransport<T>& w)
    {
        this->children().emplace_back(make_id_holder(w.id()));
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(children(), state["children"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xbox<D>::add(xtransport<T>&& w)
    {
        this->children().emplace_back(make_owning_holder(std::move(w)));
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(children(), state["children"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline enable_xtransport_t<T> xbox<D>::add(std::shared_ptr<T> w)
    {
        this->children().emplace_back(make_shared_holder<T>(w));
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(children(), state["children"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    template <class T>
    inline void xbox<D>::remove(const xtransport<T>& w)
    {
        this->children().erase(
            std::remove_if(
                this->children().begin(), this->children().end(),
                [&w](const xholder& element) {
                    return element.id() == w.id();
                }
            ),
            this->children().end()
        );
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(children(), state["children"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xbox<D>::clear()
    {
        this->children() = {};
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(children(), state["children"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
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
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
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

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xbox>;
    extern template class xtransport<xmaterialize<xbox>>;
    extern template nl::json mime_bundle_repr<xbox>(const xmaterialize<xbox>&);

    extern template class xmaterialize<xhbox>;
    extern template class xtransport<xmaterialize<xhbox>>;
    extern template nl::json mime_bundle_repr<xhbox>(const xmaterialize<xhbox>&);   

    extern template class xmaterialize<xvbox>;
    extern template class xtransport<xmaterialize<xvbox>>;
    extern template nl::json mime_bundle_repr<xvbox>(const xmaterialize<xvbox>&);
}
#endif
