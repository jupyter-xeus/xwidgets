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
    template class XWIDGETS_API xmaterialize<xhbox>;
    template xmaterialize<xhbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xhbox>>;

    template class XWIDGETS_API xmaterialize<xvbox>;
    template xmaterialize<xvbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvbox>>;
}
