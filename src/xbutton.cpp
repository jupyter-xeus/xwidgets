#include "xwidgets/xbutton.hpp"

namespace xw
{
#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xbutton_style>;
    template class xtransport<xmaterialize<xbutton_style>>;
    template nl::json mime_bundle_repr<xbutton_style>(const xmaterialize<xbutton_style>&);
#else
    template class XWIDGETS_API xmaterialize<xbutton_style>;
    template class XWIDGETS_API xtransport<xmaterialize<xbutton_style>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xbutton_style>(const xmaterialize<xbutton_style>&);
#endif

    template class XWIDGETS_API xmaterialize<xbutton>;
    template class XWIDGETS_API xtransport<xmaterialize<xbutton>>;
    template XWIDGETS_API nl::json mime_bundle_repr<xbutton>(const xmaterialize<xbutton>&);
}
