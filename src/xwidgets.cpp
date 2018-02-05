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

namespace xw
{

    template class xmaterialize<xlabel>;
    template xmaterialize<xlabel>::xmaterialize();
    template class xtransport<xmaterialize<xlabel>>;
    template class xgenerator<xlabel>;
    template xgenerator<xlabel>::xgenerator();
    template class xtransport<xgenerator<xlabel>>;

    template class xmaterialize<xhtml>;
    template xmaterialize<xhtml>::xmaterialize();
    template class xtransport<xmaterialize<xhtml>>;
    template class xgenerator<xhtml>;
    template xgenerator<xhtml>::xgenerator();
    template class xtransport<xgenerator<xhtml>>;

    template class xmaterialize<xcheckbox>;
    template xmaterialize<xcheckbox>::xmaterialize();
    template class xtransport<xmaterialize<xcheckbox>>;
    template class xgenerator<xcheckbox>;
    template xgenerator<xcheckbox>::xgenerator();
    template class xtransport<xgenerator<xcheckbox>>;

    template class xmaterialize<xplay>;
    template xmaterialize<xplay>::xmaterialize();
    template class xtransport<xmaterialize<xplay>>;
    template class xgenerator<xplay>;
    template xgenerator<xplay>::xgenerator();
    template class xtransport<xgenerator<xplay>>;

    template class xmaterialize<xpassword>;
    template xmaterialize<xpassword>::xmaterialize();
    template class xtransport<xmaterialize<xpassword>>;
    template class xgenerator<xpassword>;
    template xgenerator<xpassword>::xgenerator();
    template class xtransport<xgenerator<xpassword>>;

    template class xmaterialize<xbutton_style>;
    template xmaterialize<xbutton_style>::xmaterialize();
    template class xtransport<xmaterialize<xbutton_style>>;
    template class xgenerator<xbutton_style>;
    template xgenerator<xbutton_style>::xgenerator();
    template class xtransport<xgenerator<xbutton_style>>;

    template class xmaterialize<xbutton>;
    template xmaterialize<xbutton>::xmaterialize();
    template class xtransport<xmaterialize<xbutton>>;
    template class xgenerator<xbutton>;
    template xgenerator<xbutton>::xgenerator();
    template class xtransport<xgenerator<xbutton>>;

    template class xmaterialize<xdropdown>;
    template xmaterialize<xdropdown>::xmaterialize();
    template class xtransport<xmaterialize<xdropdown>>;
    template class xgenerator<xdropdown>;
    template xgenerator<xdropdown>::xgenerator();
    template class xtransport<xgenerator<xdropdown>>;

    template class xmaterialize<xselectionslider>;
    template xmaterialize<xselectionslider>::xmaterialize();
    template class xtransport<xmaterialize<xselectionslider>>;
    template class xgenerator<xselectionslider>;
    template xgenerator<xselectionslider>::xgenerator();
    template class xtransport<xgenerator<xselectionslider>>;

    template class xmaterialize<xselection_rangeslider>;
    template xmaterialize<xselection_rangeslider>::xmaterialize();
    template class xtransport<xmaterialize<xselection_rangeslider>>;
    template class xgenerator<xselection_rangeslider>;
    template xgenerator<xselection_rangeslider>::xgenerator();
    template class xtransport<xgenerator<xselection_rangeslider>>;

    template class xmaterialize<xprogress_style>;
    template xmaterialize<xprogress_style>::xmaterialize();
    template class xtransport<xmaterialize<xprogress_style>>;
    template class xgenerator<xprogress_style>;
    template xgenerator<xprogress_style>::xgenerator();
    template class xtransport<xgenerator<xprogress_style>>;

        
    template class xmaterialize<xprogress, int>;
    template xmaterialize<xprogress, int>::xmaterialize();
    template class xtransport<xmaterialize<xprogress, int>>;
    template class xgenerator<xprogress, int>;
    template xgenerator<xprogress, int>::xgenerator();
    template class xtransport<xgenerator<xprogress, int>>;
        
    template class xmaterialize<xprogress, float>;
    template xmaterialize<xprogress, float>::xmaterialize();
    template class xtransport<xmaterialize<xprogress, float>>;
    template class xgenerator<xprogress, float>;
    template xgenerator<xprogress, float>::xgenerator();
    template class xtransport<xgenerator<xprogress, float>>;
        
    template class xmaterialize<xprogress, double>;
    template xmaterialize<xprogress, double>::xmaterialize();
    template class xtransport<xmaterialize<xprogress, double>>;
    template class xgenerator<xprogress, double>;
    template xgenerator<xprogress, double>::xgenerator();
    template class xtransport<xgenerator<xprogress, double>>;
        

    template class xmaterialize<xcolor_picker>;
    template xmaterialize<xcolor_picker>::xmaterialize();
    template class xtransport<xmaterialize<xcolor_picker>>;
    template class xgenerator<xcolor_picker>;
    template xgenerator<xcolor_picker>::xgenerator();
    template class xtransport<xgenerator<xcolor_picker>>;

    template class xmaterialize<xtogglebuttons_style>;
    template xmaterialize<xtogglebuttons_style>::xmaterialize();
    template class xtransport<xmaterialize<xtogglebuttons_style>>;
    template class xgenerator<xtogglebuttons_style>;
    template xgenerator<xtogglebuttons_style>::xgenerator();
    template class xtransport<xgenerator<xtogglebuttons_style>>;

    template class xmaterialize<xtogglebuttons>;
    template xmaterialize<xtogglebuttons>::xmaterialize();
    template class xtransport<xmaterialize<xtogglebuttons>>;
    template class xgenerator<xtogglebuttons>;
    template xgenerator<xtogglebuttons>::xgenerator();
    template class xtransport<xgenerator<xtogglebuttons>>;

    template class xmaterialize<xlayout>;
    template xmaterialize<xlayout>::xmaterialize();
    template class xtransport<xmaterialize<xlayout>>;
    template class xgenerator<xlayout>;
    template xgenerator<xlayout>::xgenerator();
    template class xtransport<xgenerator<xlayout>>;

    template class xmaterialize<xtextarea>;
    template xmaterialize<xtextarea>::xmaterialize();
    template class xtransport<xmaterialize<xtextarea>>;
    template class xgenerator<xtextarea>;
    template xgenerator<xtextarea>::xgenerator();
    template class xtransport<xgenerator<xtextarea>>;

    template class xmaterialize<xtext>;
    template xmaterialize<xtext>::xmaterialize();
    template class xtransport<xmaterialize<xtext>>;
    template class xgenerator<xtext>;
    template xgenerator<xtext>::xgenerator();
    template class xtransport<xgenerator<xtext>>;

    template class xmaterialize<xhbox>;
    template xmaterialize<xhbox>::xmaterialize();
    template class xtransport<xmaterialize<xhbox>>;
    template class xgenerator<xhbox>;
    template xgenerator<xhbox>::xgenerator();
    template class xtransport<xgenerator<xhbox>>;

    template class xmaterialize<xvbox>;
    template xmaterialize<xvbox>::xmaterialize();
    template class xtransport<xmaterialize<xvbox>>;
    template class xgenerator<xvbox>;
    template xgenerator<xvbox>::xgenerator();
    template class xtransport<xgenerator<xvbox>>;

    template class xmaterialize<xslider_style>;
    template xmaterialize<xslider_style>::xmaterialize();
    template class xtransport<xmaterialize<xslider_style>>;
    template class xgenerator<xslider_style>;
    template xgenerator<xslider_style>::xgenerator();
    template class xtransport<xgenerator<xslider_style>>;

        
    template class xmaterialize<xslider, int>;
    template xmaterialize<xslider, int>::xmaterialize();
    template class xtransport<xmaterialize<xslider, int>>;
    template class xgenerator<xslider, int>;
    template xgenerator<xslider, int>::xgenerator();
    template class xtransport<xgenerator<xslider, int>>;
        
    template class xmaterialize<xslider, float>;
    template xmaterialize<xslider, float>::xmaterialize();
    template class xtransport<xmaterialize<xslider, float>>;
    template class xgenerator<xslider, float>;
    template xgenerator<xslider, float>::xgenerator();
    template class xtransport<xgenerator<xslider, float>>;
        
    template class xmaterialize<xslider, double>;
    template xmaterialize<xslider, double>::xmaterialize();
    template class xtransport<xmaterialize<xslider, double>>;
    template class xgenerator<xslider, double>;
    template xgenerator<xslider, double>::xgenerator();
    template class xtransport<xgenerator<xslider, double>>;
        

    template class xmaterialize<xselect>;
    template xmaterialize<xselect>::xmaterialize();
    template class xtransport<xmaterialize<xselect>>;
    template class xgenerator<xselect>;
    template xgenerator<xselect>::xgenerator();
    template class xtransport<xgenerator<xselect>>;

    template class xmaterialize<xselect_multiple>;
    template xmaterialize<xselect_multiple>::xmaterialize();
    template class xtransport<xmaterialize<xselect_multiple>>;
    template class xgenerator<xselect_multiple>;
    template xgenerator<xselect_multiple>::xgenerator();
    template class xtransport<xgenerator<xselect_multiple>>;

    template class xmaterialize<xvalid>;
    template xmaterialize<xvalid>::xmaterialize();
    template class xtransport<xmaterialize<xvalid>>;
    template class xgenerator<xvalid>;
    template xgenerator<xvalid>::xgenerator();
    template class xtransport<xgenerator<xvalid>>;

    template class xmaterialize<xradiobuttons>;
    template xmaterialize<xradiobuttons>::xmaterialize();
    template class xtransport<xmaterialize<xradiobuttons>>;
    template class xgenerator<xradiobuttons>;
    template xgenerator<xradiobuttons>::xgenerator();
    template class xtransport<xgenerator<xradiobuttons>>;

    template class xmaterialize<xaccordion>;
    template xmaterialize<xaccordion>::xmaterialize();
    template class xtransport<xmaterialize<xaccordion>>;
    template class xgenerator<xaccordion>;
    template xgenerator<xaccordion>::xgenerator();
    template class xtransport<xgenerator<xaccordion>>;

    template class xmaterialize<xtab>;
    template xmaterialize<xtab>::xmaterialize();
    template class xtransport<xmaterialize<xtab>>;
    template class xgenerator<xtab>;
    template xgenerator<xtab>::xgenerator();
    template class xtransport<xgenerator<xtab>>;

    template class xmaterialize<xtogglebutton>;
    template xmaterialize<xtogglebutton>::xmaterialize();
    template class xtransport<xmaterialize<xtogglebutton>>;
    template class xgenerator<xtogglebutton>;
    template xgenerator<xtogglebutton>::xgenerator();
    template class xtransport<xgenerator<xtogglebutton>>;


}
