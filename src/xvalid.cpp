#include "xwidgets/xvalid.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xvalid>;
    template xmaterialize<xvalid>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvalid>>;
}
