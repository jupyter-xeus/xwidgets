#include "xwidgets/xplay.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xplay>;
    template xmaterialize<xplay>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xplay>>;
    template class XWIDGETS_API xgenerator<xplay>;
    template xgenerator<xplay>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xplay>>;
}
