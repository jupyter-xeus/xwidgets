#include "xwidgets/xslider.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xslider_style>;
    template xmaterialize<xslider_style>::xmaterialize();
    template class xtransport<xmaterialize<xslider_style>>;
    template class xgenerator<xslider_style>;
    template xgenerator<xslider_style>::xgenerator();
    template class xtransport<xgenerator<xslider_style>>;
#else
    template class XWIDGETS_API xmaterialize<xslider_style>;
    template xmaterialize<xslider_style>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider_style>>;
    template class XWIDGETS_API xgenerator<xslider_style>;
    template xgenerator<xslider_style>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xslider, int>;
    template xmaterialize<xslider, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, int>>;
    template class XWIDGETS_API xgenerator<xslider, int>;
    template xgenerator<xslider, int>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, int>>;

    template class XWIDGETS_API xmaterialize<xslider, float>;
    template xmaterialize<xslider, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, float>>;
    template class XWIDGETS_API xgenerator<xslider, float>;
    template xgenerator<xslider, float>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, float>>;

    template class XWIDGETS_API xmaterialize<xslider, double>;
    template xmaterialize<xslider, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, double>>;
    template class XWIDGETS_API xgenerator<xslider, double>;
    template xgenerator<xslider, double>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, double>>;
}
