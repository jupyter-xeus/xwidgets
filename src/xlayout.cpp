#include "xwidgets/xlayout.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xlayout>;
    template xmaterialize<xlayout>::xmaterialize();
    template class xtransport<xmaterialize<xlayout>>;
#else
    template class XWIDGETS_API xmaterialize<xlayout>;
    template xmaterialize<xlayout>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xlayout>>;
#endif
}
