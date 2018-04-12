#include "xwidgets/xnumeral.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xnumeral, int>;
    template xmaterialize<xnumeral, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, int>>;
    template class XWIDGETS_API xgenerator<xnumeral, int>;
    template xgenerator<xnumeral, int>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xnumeral, int>>;

    template class XWIDGETS_API xmaterialize<xnumeral, float>;
    template xmaterialize<xnumeral, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, float>>;
    template class XWIDGETS_API xgenerator<xnumeral, float>;
    template xgenerator<xnumeral, float>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xnumeral, float>>;

    template class XWIDGETS_API xmaterialize<xnumeral, double>;
    template xmaterialize<xnumeral, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xnumeral, double>>;
    template class XWIDGETS_API xgenerator<xnumeral, double>;
    template xgenerator<xnumeral, double>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xnumeral, double>>;
}
