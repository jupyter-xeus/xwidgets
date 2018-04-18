#include "xwidgets/ximage.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<ximage>;
    template xmaterialize<ximage>::xmaterialize();
    template class xtransport<xmaterialize<ximage>>;
    template class xgenerator<ximage>;
    template xgenerator<ximage>::xgenerator();
    template class xtransport<xgenerator<ximage>>;
#else
    template class XWIDGETS_API xmaterialize<ximage>;
    template xmaterialize<ximage>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<ximage>>;
    template class XWIDGETS_API xgenerator<ximage>;
    template xgenerator<ximage>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<ximage>>;
#endif
}
