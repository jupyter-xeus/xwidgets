/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_LINK_HPP
#define XWIDGETS_LINK_HPP

#include <string>
#include <tuple>
#include <utility>

#include "xholder.hpp"
#include "xmaterialize.hpp"
#include "xobject.hpp"

namespace xw
{
    /********************
     * link declaration *
     ********************/

    using xlink_pair_type = std::tuple<xholder<xtransport>, std::string>;

    template <class D>
    class xlink : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        using pair_type = xlink_pair_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(pair_type, derived_type, source);
        XPROPERTY(pair_type, derived_type, target);

    protected:

        template <class S, class T>
        xlink(xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using link = xmaterialize<xlink>;

    using link_generator = xgenerator<xlink>;

    /********************************
     * directional_link declaration *
     ********************************/

    using xdirectional_link_pair_type = std::tuple<xholder<xtransport>, std::string>;

    template <class D>
    class xdirectional_link : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        using pair_type = xdirectional_link_pair_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(pair_type, derived_type, source);
        XPROPERTY(pair_type, derived_type, target);

    protected:

        template <class S, class T>
        xdirectional_link(const xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using directional_link = xmaterialize<xdirectional_link>;

    using directional_link_generator = xgenerator<xdirectional_link>;

    /************************
     * xlink implementation *
     ************************/

    template <class D>
    inline void xlink<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(source(), state["source"], buffers);
        xwidgets_serialize(target(), state["target"], buffers);
    }

    template <class D>
    inline void xlink<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(source, patch, buffers);
        set_property_from_patch(target, patch, buffers);
    }

    template <class D>
    template <class S, class T>
    inline xlink<D>::xlink(xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn)
        : base_type()
    {
        set_defaults();
        std::get<0>(this->source()) = s;
        std::get<1>(this->source()) = sn;
        std::get<0>(this->target()) = t;
        std::get<1>(this->target()) = tn;
    }

    template <class D>
    inline void xlink<D>::set_defaults()
    {
        this->_model_name() = "LinkModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /************************************
     * xdirectional_link implementation *
     ************************************/

    template <class D>
    inline void xdirectional_link<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(source(), state["source"], buffers);
        xwidgets_serialize(target(), state["target"], buffers);
    }

    template <class D>
    inline void xdirectional_link<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(source, patch, buffers);
        set_property_from_patch(target, patch, buffers);
    }

    template <class D>
    template <class S, class T>
    inline xdirectional_link<D>::xdirectional_link(const xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn)
        : base_type()
    {
        set_defaults();
        std::get<0>(this->source()) = s;
        std::get<1>(this->source()) = sn;
        std::get<0>(this->target()) = t;
        std::get<1>(this->target()) = tn;
    }

    template <class D>
    inline void xdirectional_link<D>::set_defaults()
    {
        this->_model_name() = "DirectionalLinkModel";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xlink>;
    extern template class xtransport<xmaterialize<xlink>>;
    extern template class xgenerator<xlink>;
    extern template class xtransport<xgenerator<xlink>>;

    extern template class xmaterialize<xdirectional_link>;
    extern template class xtransport<xmaterialize<xdirectional_link>>;
    extern template class xgenerator<xdirectional_link>;
    extern template class xtransport<xgenerator<xdirectional_link>>;
#endif
}
#endif
