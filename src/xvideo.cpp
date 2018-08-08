#include "xwidgets/xvideo.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xvideo>;
    template xmaterialize<xvideo>::xmaterialize();
    template class xtransport<xmaterialize<xvideo>>;
    template class xgenerator<xvideo>;
    template xgenerator<xvideo>::xgenerator();
    template class xtransport<xgenerator<xvideo>>;
#else
    template class XWIDGETS_API xmaterialize<xvideo>;
    template xmaterialize<xvideo>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvideo>>;
    template class XWIDGETS_API xgenerator<xvideo>;
    template xgenerator<xvideo>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xvideo>>;
#endif
}
