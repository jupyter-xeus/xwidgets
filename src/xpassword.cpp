#include "xwidgets/xpassword.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xpassword>;
    template xmaterialize<xpassword>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xpassword>>;
    template class XWIDGETS_API xgenerator<xpassword>;
    template xgenerator<xpassword>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xpassword>>;
}
