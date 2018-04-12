#include "xwidgets/xhtml.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xhtml>;
    template xmaterialize<xhtml>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xhtml>>;
    template class XWIDGETS_API xgenerator<xhtml>;
    template xgenerator<xhtml>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xhtml>>;
}
