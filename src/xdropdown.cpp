#include "xwidgets/xdropdown.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xdropdown>;
    template xmaterialize<xdropdown>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xdropdown>>;
}
