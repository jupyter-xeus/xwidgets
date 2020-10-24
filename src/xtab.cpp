/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "xwidgets/xtab.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtab>;
    template class XWIDGETS_API xtransport<xmaterialize<xtab>>;
}
