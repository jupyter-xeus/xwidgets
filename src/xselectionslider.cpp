#include "xwidgets/xselectionslider.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xselectionslider>;
    template xmaterialize<xselectionslider>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselectionslider>>;

    template class XWIDGETS_API xmaterialize<xselection_rangeslider>;
    template xmaterialize<xselection_rangeslider>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselection_rangeslider>>;
}
