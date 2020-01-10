#include "xwidgets/xcolor_picker.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcolor_picker>;
    template xmaterialize<xcolor_picker>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcolor_picker>>;
}
