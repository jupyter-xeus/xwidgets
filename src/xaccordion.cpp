#include "xwidgets/xaccordion.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xaccordion>;
    template class XWIDGETS_API xtransport<xmaterialize<xaccordion>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xaccordion>(const xmaterialize<xaccordion>&);
}
