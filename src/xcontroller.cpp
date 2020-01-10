#include "xwidgets/xcontroller.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcontroller_button>;
    template xmaterialize<xcontroller_button>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_button>>;

    template class XWIDGETS_API xmaterialize<xcontroller_axis>;
    template xmaterialize<xcontroller_axis>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_axis>>;

    template class XWIDGETS_API xmaterialize<xcontroller>;
    template xmaterialize<xcontroller>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller>>;
}
