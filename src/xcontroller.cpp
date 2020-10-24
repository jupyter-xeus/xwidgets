#include "xwidgets/xcontroller.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcontroller_button>;
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_button>>;

    template class XWIDGETS_API xmaterialize<xcontroller_axis>;
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_axis>>;

    template class XWIDGETS_API xmaterialize<xcontroller>;
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller>>;
}
