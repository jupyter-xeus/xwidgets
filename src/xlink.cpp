#include "xwidgets/xlink.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xlink>;
    template class XWIDGETS_API xtransport<xmaterialize<xlink>>;
    template class XWIDGETS_API xgenerator<xlink>;
    template class XWIDGETS_API xtransport<xgenerator<xlink>>;

    template class XWIDGETS_API xmaterialize<xdirectional_link>;
    template class XWIDGETS_API xtransport<xmaterialize<xdirectional_link>>;
    template class XWIDGETS_API xgenerator<xdirectional_link>;
    template class XWIDGETS_API xtransport<xgenerator<xdirectional_link>>;
}
