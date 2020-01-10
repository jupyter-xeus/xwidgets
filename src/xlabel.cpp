#include "xwidgets/xlabel.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xlabel>;
    template xmaterialize<xlabel>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xlabel>>;
}
