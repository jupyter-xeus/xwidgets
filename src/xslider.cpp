#include "xwidgets/xslider.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER == 1910 || _MSC_VER == 1911 || _MSC_VER == 1912 || _MSC_VER == 1913)
    template class xmaterialize<xslider_style>;
    template class xtransport<xmaterialize<xslider_style>>;
#else
    template class XWIDGETS_API xmaterialize<xslider_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xslider, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, int>>;

    template class XWIDGETS_API xmaterialize<xslider, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, float>>;

    template class XWIDGETS_API xmaterialize<xslider, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xslider, double>>;
}
