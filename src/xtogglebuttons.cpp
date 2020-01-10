#include "xwidgets/xtogglebuttons.hpp"

namespace xw
{
	#if defined(_MSC_VER) && (_MSC_VER==1910 || _MSC_VER==1911 || _MSC_VER==1912 || _MSC_VER==1913)
    template class xmaterialize<xtogglebuttons_style>;
    template xmaterialize<xtogglebuttons_style>::xmaterialize();
    template class xtransport<xmaterialize<xtogglebuttons_style>>;
#else
    template class XWIDGETS_API xmaterialize<xtogglebuttons_style>;
    template xmaterialize<xtogglebuttons_style>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtogglebuttons_style>>;
#endif

    template class XWIDGETS_API xmaterialize<xtogglebuttons>;
    template xmaterialize<xtogglebuttons>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtogglebuttons>>;
}