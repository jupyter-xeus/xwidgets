#include "xwidgets/xnumeral.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xnumeral, int>;
    template xmaterialize<xnumeral, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, int>>;

    template class XWIDGETS_API xmaterialize<xnumeral, float>;
    template xmaterialize<xnumeral, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, float>>;

    template class XWIDGETS_API xmaterialize<xnumeral, double>;
    template xmaterialize<xnumeral, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, double>>;
}
