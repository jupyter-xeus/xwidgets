#include "xwidgets/xbutton.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xbutton_style>;
    template xmaterialize<xbutton_style>::xmaterialize();
    template class xtransport<xmaterialize<xbutton_style>>;
    template class xgenerator<xbutton_style>;
    template xgenerator<xbutton_style>::xgenerator();
    template class xtransport<xgenerator<xbutton_style>>;
#else
    template class XWIDGETS_API xmaterialize<xbutton_style>;
    template xmaterialize<xbutton_style>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xbutton_style>>;
    template class XWIDGETS_API xgenerator<xbutton_style>;
    template xgenerator<xbutton_style>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xbutton_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xbutton>;
    template xmaterialize<xbutton>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xbutton>>;
    template class XWIDGETS_API xgenerator<xbutton>;
    template xgenerator<xbutton>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xbutton>>;
}
