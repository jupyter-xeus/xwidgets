#include "xwidgets/xaudio.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xaudio>;
    template xmaterialize<xaudio>::xmaterialize();
    template class xtransport<xmaterialize<xaudio>>;
    template class xgenerator<xaudio>;
    template xgenerator<xaudio>::xgenerator();
    template class xtransport<xgenerator<xaudio>>;
#else
    template class XWIDGETS_API xmaterialize<xaudio>;
    template xmaterialize<xaudio>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xaudio>>;
    template class XWIDGETS_API xgenerator<xaudio>;
    template xgenerator<xaudio>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xaudio>>;
#endif
}
