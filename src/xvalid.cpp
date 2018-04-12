#include "xwidgets/xvalid.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xvalid>;
    template xmaterialize<xvalid>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvalid>>;
    template class XWIDGETS_API xgenerator<xvalid>;
    template xgenerator<xvalid>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xvalid>>;
}
