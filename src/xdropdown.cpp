#include "xwidgets/xdropdown.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xdropdown>;
    template xmaterialize<xdropdown>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xdropdown>>;
    template class XWIDGETS_API xgenerator<xdropdown>;
    template xgenerator<xdropdown>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xdropdown>>;
}
