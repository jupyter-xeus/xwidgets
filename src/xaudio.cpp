#include "xwidgets/xaudio.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xaudio>;
    template class xtransport<xmaterialize<xaudio>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xaudio>(const xmaterialize<xaudio>&);
#else
    template class XWIDGETS_API xmaterialize<xaudio>;
    template class XWIDGETS_API xtransport<xmaterialize<xaudio>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xaudio>(const xmaterialize<xaudio>&);
#endif
}
