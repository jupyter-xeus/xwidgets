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
