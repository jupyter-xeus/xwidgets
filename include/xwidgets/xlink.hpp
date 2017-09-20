/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_LINK_HPP
#define XWIDGETS_LINK_HPP

#include <utility>

#include "xholder.hpp"
#include "xholder_id.hpp"
#include "xmaterialize.hpp"
#include "xobject.hpp"

namespace std
{
    template <class A, class B>
    inline void to_json(xeus::xjson& j, const std::pair<A, B>& o)
    {
        j[0] = o.first;
        j[1] = o.second;
    }

    template <class A, class B>
    inline void from_json(const xeus::xjson& j, std::pair<A, B>& o)
    {
        o.first = j[0].get<A>();
        o.second = j[1].get<B>();
    }
}

namespace xw
{
    /********************
     * link declaration *
     ********************/

    using xlink_pair_type = std::pair<xholder<xtransport>, std::string>;

    template <class D>
    class xlink : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        using pair_type = xlink_pair_type;

        xlink();
        template <class S, class T>
        xlink(xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn);
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(pair_type, derived_type, source);
        XPROPERTY(pair_type, derived_type, target);

    private:

        void set_defaults();
    };

    using link = xmaterialize<xlink>;

    /************************
     * xlink implementation *
     ************************/

    template <class D>
    inline xlink<D>::xlink()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class S, class T>
    inline xlink<D>::xlink(xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn)
        : base_type()
    {
        set_defaults();
        this->source().first = s;
        this->source().second = sn;
        this->target().first = t;
        this->target().second = tn;
    }

    template <class D>
    inline xeus::xjson xlink<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(source, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(target, state);

        return state;
    }

    template <class D>
    inline void xlink<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(source, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(target, patch)
    }

    template <class D>
    inline void xlink<D>::set_defaults()
    {
        this->_model_name() = "LinkModel";
        this->_model_module() = "@jupyter-widgets/controls";
    }

    template <class S, class T>
    inline link make_link(xtransport<S>& s, std::string sn, xtransport<T>& t, std::string tn)
    {
        link l;
        l.source().first = s;
        l.source().second = sn;
        l.target().first = t;
        l.target().second = tn;
        l.send_patch(l.get_state());
        return l;
    }
}

#endif
