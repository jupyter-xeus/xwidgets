#include "xwidgets/xoutput.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xoutput>;
    template xmaterialize<xoutput>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xoutput>>;
}
