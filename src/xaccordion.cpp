#include "xwidgets/xaccordion.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xaccordion>;
    template xmaterialize<xaccordion>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xaccordion>>;
    template class XWIDGETS_API xgenerator<xaccordion>;
    template xgenerator<xaccordion>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xaccordion>>;
}
