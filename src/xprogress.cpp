#include "xwidgets/xprogress.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER == 1910 || _MSC_VER == 1911 || _MSC_VER == 1912 || _MSC_VER == 1913)
    template class xmaterialize<xprogress_style>;
    template class xtransport<xmaterialize<xprogress_style>>;
#else
    template class XWIDGETS_API xmaterialize<xprogress_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xprogress, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, int>>;

    template class XWIDGETS_API xmaterialize<xprogress, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, float>>;

    template class XWIDGETS_API xmaterialize<xprogress, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, double>>;
}
