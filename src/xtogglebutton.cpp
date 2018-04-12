#include "xwidgets/xtogglebutton.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtogglebutton>;
    template xmaterialize<xtogglebutton>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtogglebutton>>;
    template class XWIDGETS_API xgenerator<xtogglebutton>;
    template xgenerator<xtogglebutton>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtogglebutton>>;
}
