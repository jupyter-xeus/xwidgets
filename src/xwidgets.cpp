#include "xwidgets/xaccordion.hpp"
#include "xwidgets/xcheckbox.hpp"
#include "xwidgets/xselect.hpp"
#include "xwidgets/xslider.hpp"
#include "xwidgets/xbox.hpp"
#include "xwidgets/xselectionslider.hpp"
#include "xwidgets/xtogglebuttons.hpp"
#include "xwidgets/xhtml.hpp"
#include "xwidgets/xbutton.hpp"
#include "xwidgets/xpassword.hpp"
#include "xwidgets/xlabel.hpp"
#include "xwidgets/xlayout.hpp"
#include "xwidgets/xprogress.hpp"
#include "xwidgets/xplay.hpp"
#include "xwidgets/xdropdown.hpp"
#include "xwidgets/xcolor_picker.hpp"
#include "xwidgets/xtogglebutton.hpp"
#include "xwidgets/xtext.hpp"
#include "xwidgets/xradiobuttons.hpp"
#include "xwidgets/xtab.hpp"
#include "xwidgets/xtextarea.hpp"
#include "xwidgets/xvalid.hpp"
#include "xwidgets/xprecompiled_macros.hpp"

namespace xw
{
    XPRECOMPILE((NO_EXTERN, XWIDGETS_API),
               (xlabel,
                xhtml,
                xcheckbox,
                xpassword,
                xplay,
                xbutton_style,
                xbutton,
                xdropdown,
                xselectionslider,
                xselection_rangeslider,
                xprogress_style,
                xcolor_picker,
                xtogglebuttons_style,
                xtogglebuttons,
                xtogglebutton,
                xlayout,
                xtext,
                xtextarea,
                xhbox,
                xvbox,
                xslider_style,
                xselect,
                xselect_multiple,
                xvalid,
                xradiobuttons,
                xaccordion,
                xtab
                ));

   XPRECOMPILE_WITH_TYPES((NO_EXTERN, XWIDGETS_API), (xprogress, xslider), (int, float, double));
}
