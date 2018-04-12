#include "xwidgets/xcontroller.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcontroller_button>;
    template xmaterialize<xcontroller_button>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_button>>;
    template class XWIDGETS_API xgenerator<xcontroller_button>;
    template xgenerator<xcontroller_button>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller_button>>;

    template class XWIDGETS_API xmaterialize<xcontroller_axis>;
    template xmaterialize<xcontroller_axis>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_axis>>;
    template class XWIDGETS_API xgenerator<xcontroller_axis>;
    template xgenerator<xcontroller_axis>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller_axis>>;

    template class XWIDGETS_API xmaterialize<xcontroller>;
    template xmaterialize<xcontroller>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller>>;
    template class XWIDGETS_API xgenerator<xcontroller>;
    template xgenerator<xcontroller>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller>>;
}
