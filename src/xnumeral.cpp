#include "xwidgets/xnumeral.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xnumeral, int>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, int>>;

    template class XWIDGETS_API xmaterialize<xnumeral, float>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, float>>;

    template class XWIDGETS_API xmaterialize<xnumeral, double>;
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, double>>;
}
