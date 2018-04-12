#include "xwidgets/xtab.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtab>;
    template xmaterialize<xtab>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtab>>;
    template class XWIDGETS_API xgenerator<xtab>;
    template xgenerator<xtab>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtab>>;
}
