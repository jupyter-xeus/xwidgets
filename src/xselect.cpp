#include "xwidgets/xselect.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xselect>;
    template class XWIDGETS_API xtransport<xmaterialize<xselect>>;

    template class XWIDGETS_API xmaterialize<xselect_multiple>;
    template class XWIDGETS_API xtransport<xmaterialize<xselect_multiple>>;
}
