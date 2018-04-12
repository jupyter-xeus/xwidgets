#include "xwidgets/xprogress.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xprogress_style>;
    template xmaterialize<xprogress_style>::xmaterialize();
    template class xtransport<xmaterialize<xprogress_style>>;
    template class xgenerator<xprogress_style>;
    template xgenerator<xprogress_style>::xgenerator();
    template class xtransport<xgenerator<xprogress_style>>;
#else
    template class XWIDGETS_API xmaterialize<xprogress_style>;
    template xmaterialize<xprogress_style>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress_style>>;
    template class XWIDGETS_API xgenerator<xprogress_style>;
    template xgenerator<xprogress_style>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xprogress, int>;
    template xmaterialize<xprogress, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, int>>;
    template class XWIDGETS_API xgenerator<xprogress, int>;
    template xgenerator<xprogress, int>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, int>>;

    template class XWIDGETS_API xmaterialize<xprogress, float>;
    template xmaterialize<xprogress, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, float>>;
    template class XWIDGETS_API xgenerator<xprogress, float>;
    template xgenerator<xprogress, float>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, float>>;

    template class XWIDGETS_API xmaterialize<xprogress, double>;
    template xmaterialize<xprogress, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, double>>;
    template class XWIDGETS_API xgenerator<xprogress, double>;
    template xgenerator<xprogress, double>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, double>>;
}