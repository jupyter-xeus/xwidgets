#include "xwidgets/xcolor_picker.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcolor_picker>;
    template xmaterialize<xcolor_picker>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcolor_picker>>;
    template class XWIDGETS_API xgenerator<xcolor_picker>;
    template xgenerator<xcolor_picker>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcolor_picker>>;
}
