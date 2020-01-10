#include "xwidgets/xtext.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xtext>;
    template xmaterialize<xtext>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtext>>;
}
