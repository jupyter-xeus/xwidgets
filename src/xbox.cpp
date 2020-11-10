/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "xwidgets/xbox.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xbox>;
    template class XWIDGETS_API xtransport<xmaterialize<xbox>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xbox>(const xmaterialize<xbox>&);

    template class XWIDGETS_API xmaterialize<xhbox>;
    template class XWIDGETS_API xtransport<xmaterialize<xhbox>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xhbox>(const xmaterialize<xhbox>&);

    template class XWIDGETS_API xmaterialize<xvbox>;
    template class XWIDGETS_API xtransport<xmaterialize<xvbox>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xvbox>(const xmaterialize<xvbox>&);
}
