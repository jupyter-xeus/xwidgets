#include "xwidgets/xplay.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xplay>;
    template xmaterialize<xplay>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xplay>>;
}
