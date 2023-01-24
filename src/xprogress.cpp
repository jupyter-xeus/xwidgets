/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xprogress.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xprogress_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress_style>>;

    template class XWIDGETS_API xmaterialize<xprogress, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, int>>;

    template class XWIDGETS_API xmaterialize<xprogress, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, float>>;

    template class XWIDGETS_API xmaterialize<xprogress, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, double>>;
}
