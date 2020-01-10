#include "xwidgets/xpassword.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xpassword>;
    template xmaterialize<xpassword>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xpassword>>;
}
