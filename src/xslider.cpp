/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xslider.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xslider_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider_style>>;

    template class XWIDGETS_API xmaterialize<xslider, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, int>>;

    template class XWIDGETS_API xmaterialize<xslider, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, float>>;

    template class XWIDGETS_API xmaterialize<xslider, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, double>>;
}
