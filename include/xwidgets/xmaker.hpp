/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_MAKER_HPP
#define XWIDGETS_MAKER_HPP

#include "xeus/xcomm.hpp"
#include "xeus/xjson.hpp"
#include "xeus/xmessage.hpp"

#include "xholder.hpp"
#include "xmaterialize.hpp"

namespace xw
{
    /*******************
     * xmaker template *
     *******************/

    template <template <class> class CRTP, class... P>
    void xmaker(xeus::xcomm&& comm, const xeus::xjson& state, const xeus::buffer_sequence& buffers)
    {
        auto model = xgenerator<CRTP, P...>(std::move(comm), true);
        model.apply_patch(state, buffers);
        get_transport_registry().register_owning(reinterpret_cast<xmaterialize<CRTP, P...>&&>(model));
    }
}

#endif
