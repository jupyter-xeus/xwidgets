/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xnumber_bounded.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xnumber_bounded, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumber_bounded, int>>;

    template class XWIDGETS_API xmaterialize<xnumber_bounded, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumber_bounded, float>>;

    template class XWIDGETS_API xmaterialize<xnumber_bounded, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumber_bounded, double>>;
}
