#include "xwidgets/xselect.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xselect>;
    template xmaterialize<xselect>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselect>>;

    template class XWIDGETS_API xmaterialize<xselect_multiple>;
    template xmaterialize<xselect_multiple>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselect_multiple>>;
}