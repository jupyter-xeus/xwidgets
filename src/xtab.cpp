#include "xwidgets/xtab.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtab>;
    template xmaterialize<xtab>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtab>>;
}
