#include "xwidgets/xtextarea.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtextarea>;
    template xmaterialize<xtextarea>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtextarea>>;
}
