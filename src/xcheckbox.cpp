#include "xwidgets/xcheckbox.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xcheckbox>;
    template xmaterialize<xcheckbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcheckbox>>;
    template class XWIDGETS_API xgenerator<xcheckbox>;
    template xgenerator<xcheckbox>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcheckbox>>;
}
