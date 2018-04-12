#include "xwidgets/xradiobuttons.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xradiobuttons>;
    template xmaterialize<xradiobuttons>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xradiobuttons>>;
    template class XWIDGETS_API xgenerator<xradiobuttons>;
    template xgenerator<xradiobuttons>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xradiobuttons>>;
}
