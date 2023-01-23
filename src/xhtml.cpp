#include "xwidgets/xhtml.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xhtml_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xhtml_style>>;

    template class XWIDGETS_API xmaterialize<xhtml>;
    template class XWIDGETS_API xtransport<xmaterialize<xhtml>>;
}
