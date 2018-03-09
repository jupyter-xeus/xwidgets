#include "xwidgets/xaccordion.hpp"
#include "xwidgets/xcheckbox.hpp"
#include "xwidgets/xselect.hpp"
#include "xwidgets/xslider.hpp"
#include "xwidgets/xcontroller.hpp"
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
#include "xwidgets/xlink.hpp"
#include "xwidgets/xtab.hpp"
#include "xwidgets/xtextarea.hpp"
#include "xwidgets/xvalid.hpp"

namespace xw
{
    template class XWIDGETS_API xmaterialize<xlabel>;
    template xmaterialize<xlabel>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xlabel>>;
    template class XWIDGETS_API xgenerator<xlabel>;
    template xgenerator<xlabel>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xlabel>>;

    template class XWIDGETS_API xmaterialize<xhtml>;
    template xmaterialize<xhtml>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xhtml>>;
    template class XWIDGETS_API xgenerator<xhtml>;
    template xgenerator<xhtml>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xhtml>>;

    template class XWIDGETS_API xmaterialize<xcheckbox>;
    template xmaterialize<xcheckbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcheckbox>>;
    template class XWIDGETS_API xgenerator<xcheckbox>;
    template xgenerator<xcheckbox>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcheckbox>>;

    template class XWIDGETS_API xmaterialize<xplay>;
    template xmaterialize<xplay>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xplay>>;
    template class XWIDGETS_API xgenerator<xplay>;
    template xgenerator<xplay>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xplay>>;

    template class XWIDGETS_API xmaterialize<xpassword>;
    template xmaterialize<xpassword>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xpassword>>;
    template class XWIDGETS_API xgenerator<xpassword>;
    template xgenerator<xpassword>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xpassword>>;

    template class xmaterialize<xbutton_style>;
    template xmaterialize<xbutton_style>::xmaterialize();
    template class xtransport<xmaterialize<xbutton_style>>;
    template class xgenerator<xbutton_style>;
    template xgenerator<xbutton_style>::xgenerator();
    template class xtransport<xgenerator<xbutton_style>>;

    template class XWIDGETS_API xmaterialize<xbutton>;
    template xmaterialize<xbutton>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xbutton>>;
    template class XWIDGETS_API xgenerator<xbutton>;
    template xgenerator<xbutton>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xbutton>>;

    template class XWIDGETS_API xmaterialize<xdropdown>;
    template xmaterialize<xdropdown>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xdropdown>>;
    template class XWIDGETS_API xgenerator<xdropdown>;
    template xgenerator<xdropdown>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xdropdown>>;

    template class XWIDGETS_API xmaterialize<xselectionslider>;
    template xmaterialize<xselectionslider>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselectionslider>>;
    template class XWIDGETS_API xgenerator<xselectionslider>;
    template xgenerator<xselectionslider>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xselectionslider>>;

    template class XWIDGETS_API xmaterialize<xselection_rangeslider>;
    template xmaterialize<xselection_rangeslider>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselection_rangeslider>>;
    template class XWIDGETS_API xgenerator<xselection_rangeslider>;
    template xgenerator<xselection_rangeslider>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xselection_rangeslider>>;

    template class xmaterialize<xprogress_style>;
    template xmaterialize<xprogress_style>::xmaterialize();
    template class xtransport<xmaterialize<xprogress_style>>;
    template class xgenerator<xprogress_style>;
    template xgenerator<xprogress_style>::xgenerator();
    template class xtransport<xgenerator<xprogress_style>>;

    template class XWIDGETS_API xmaterialize<xprogress, int>;
    template xmaterialize<xprogress, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, int>>;
    template class XWIDGETS_API xgenerator<xprogress, int>;
    template xgenerator<xprogress, int>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, int>>;

    template class XWIDGETS_API xmaterialize<xprogress, float>;
    template xmaterialize<xprogress, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, float>>;
    template class XWIDGETS_API xgenerator<xprogress, float>;
    template xgenerator<xprogress, float>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, float>>;

    template class XWIDGETS_API xmaterialize<xprogress, double>;
    template xmaterialize<xprogress, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xprogress, double>>;
    template class XWIDGETS_API xgenerator<xprogress, double>;
    template xgenerator<xprogress, double>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xprogress, double>>;

    template class XWIDGETS_API xmaterialize<xcolor_picker>;
    template xmaterialize<xcolor_picker>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcolor_picker>>;
    template class XWIDGETS_API xgenerator<xcolor_picker>;
    template xgenerator<xcolor_picker>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcolor_picker>>;

    template class xmaterialize<xtogglebuttons_style>;
    template xmaterialize<xtogglebuttons_style>::xmaterialize();
    template class xtransport<xmaterialize<xtogglebuttons_style>>;
    template class xgenerator<xtogglebuttons_style>;
    template xgenerator<xtogglebuttons_style>::xgenerator();
    template class xtransport<xgenerator<xtogglebuttons_style>>;

    template class XWIDGETS_API xmaterialize<xtogglebuttons>;
    template xmaterialize<xtogglebuttons>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtogglebuttons>>;
    template class XWIDGETS_API xgenerator<xtogglebuttons>;
    template xgenerator<xtogglebuttons>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtogglebuttons>>;

    template class xmaterialize<xlayout>;
    template xmaterialize<xlayout>::xmaterialize();
    template class xtransport<xmaterialize<xlayout>>;
    template class xgenerator<xlayout>;
    template xgenerator<xlayout>::xgenerator();
    template class xtransport<xgenerator<xlayout>>;

    template class XWIDGETS_API xmaterialize<xtextarea>;
    template xmaterialize<xtextarea>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtextarea>>;
    template class XWIDGETS_API xgenerator<xtextarea>;
    template xgenerator<xtextarea>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtextarea>>;

    template class XWIDGETS_API xmaterialize<xtext>;
    template xmaterialize<xtext>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtext>>;
    template class XWIDGETS_API xgenerator<xtext>;
    template xgenerator<xtext>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtext>>;

    template class XWIDGETS_API xmaterialize<xhbox>;
    template xmaterialize<xhbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xhbox>>;
    template class XWIDGETS_API xgenerator<xhbox>;
    template xgenerator<xhbox>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xhbox>>;

    template class XWIDGETS_API xmaterialize<xvbox>;
    template xmaterialize<xvbox>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvbox>>;
    template class XWIDGETS_API xgenerator<xvbox>;
    template xgenerator<xvbox>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xvbox>>;

    template class xmaterialize<xslider_style>;
    template xmaterialize<xslider_style>::xmaterialize();
    template class xtransport<xmaterialize<xslider_style>>;
    template class xgenerator<xslider_style>;
    template xgenerator<xslider_style>::xgenerator();
    template class xtransport<xgenerator<xslider_style>>;

    template class XWIDGETS_API xmaterialize<xslider, int>;
    template xmaterialize<xslider, int>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, int>>;
    template class XWIDGETS_API xgenerator<xslider, int>;
    template xgenerator<xslider, int>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, int>>;

    template class XWIDGETS_API xmaterialize<xslider, float>;
    template xmaterialize<xslider, float>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, float>>;
    template class XWIDGETS_API xgenerator<xslider, float>;
    template xgenerator<xslider, float>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, float>>;

    template class XWIDGETS_API xmaterialize<xslider, double>;
    template xmaterialize<xslider, double>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xslider, double>>;
    template class XWIDGETS_API xgenerator<xslider, double>;
    template xgenerator<xslider, double>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xslider, double>>;

    template class XWIDGETS_API xmaterialize<xselect>;
    template xmaterialize<xselect>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselect>>;
    template class XWIDGETS_API xgenerator<xselect>;
    template xgenerator<xselect>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xselect>>;

    template class XWIDGETS_API xmaterialize<xselect_multiple>;
    template xmaterialize<xselect_multiple>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xselect_multiple>>;
    template class XWIDGETS_API xgenerator<xselect_multiple>;
    template xgenerator<xselect_multiple>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xselect_multiple>>;

    template class XWIDGETS_API xmaterialize<xvalid>;
    template xmaterialize<xvalid>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xvalid>>;
    template class XWIDGETS_API xgenerator<xvalid>;
    template xgenerator<xvalid>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xvalid>>;

    template class XWIDGETS_API xmaterialize<xradiobuttons>;
    template xmaterialize<xradiobuttons>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xradiobuttons>>;
    template class XWIDGETS_API xgenerator<xradiobuttons>;
    template xgenerator<xradiobuttons>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xradiobuttons>>;

    template class XWIDGETS_API xmaterialize<xaccordion>;
    template xmaterialize<xaccordion>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xaccordion>>;
    template class XWIDGETS_API xgenerator<xaccordion>;
    template xgenerator<xaccordion>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xaccordion>>;

    template class XWIDGETS_API xmaterialize<xtab>;
    template xmaterialize<xtab>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtab>>;
    template class XWIDGETS_API xgenerator<xtab>;
    template xgenerator<xtab>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtab>>;

    template class XWIDGETS_API xmaterialize<xtogglebutton>;
    template xmaterialize<xtogglebutton>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xtogglebutton>>;
    template class XWIDGETS_API xgenerator<xtogglebutton>;
    template xgenerator<xtogglebutton>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xtogglebutton>>;

    template class XWIDGETS_API xmaterialize<xcontroller_button>;
    template xmaterialize<xcontroller_button>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_button>>;
    template class XWIDGETS_API xgenerator<xcontroller_button>;
    template xgenerator<xcontroller_button>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller_button>>;

    template class XWIDGETS_API xmaterialize<xcontroller_axis>;
    template xmaterialize<xcontroller_axis>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller_axis>>;
    template class XWIDGETS_API xgenerator<xcontroller_axis>;
    template xgenerator<xcontroller_axis>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller_axis>>;

    template class XWIDGETS_API xmaterialize<xcontroller>;
    template xmaterialize<xcontroller>::xmaterialize();
    template class XWIDGETS_API xtransport<xmaterialize<xcontroller>>;
    template class XWIDGETS_API xgenerator<xcontroller>;
    template xgenerator<xcontroller>::xgenerator();
    template class XWIDGETS_API xtransport<xgenerator<xcontroller>>;

    template class XWIDGETS_API xmaterialize<xlink>;
    template class XWIDGETS_API xtransport<xmaterialize<xlink>>;
    template class XWIDGETS_API xgenerator<xlink>;
    template class XWIDGETS_API xtransport<xgenerator<xlink>>;

    template class XWIDGETS_API xmaterialize<xdirectional_link>;
    template class XWIDGETS_API xtransport<xmaterialize<xdirectional_link>>;
    template class XWIDGETS_API xgenerator<xdirectional_link>;
    template class XWIDGETS_API xtransport<xgenerator<xdirectional_link>>;
}
