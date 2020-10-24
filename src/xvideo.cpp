#include "xwidgets/xvideo.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xvideo>;
    template class xtransport<xmaterialize<xvideo>>;
#else
    template class XWIDGETS_API xmaterialize<xvideo>;
    template class XWIDGETS_API xtransport<xmaterialize<xvideo>>;
#endif
}
