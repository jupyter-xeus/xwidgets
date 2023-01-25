/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/ximage.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<ximage>;
    template class XWIDGETS_API xtransport<xmaterialize<ximage>>;
}
