
#ifndef XWIDGETS_XPRECOMPILED_HPP
#define XWIDGETS_XPRECOMPILED_HPP

#include "xaccordion.hpp"
#include "xcheckbox.hpp"
#include "xselect.hpp"
#include "xslider.hpp"
#include "xbox.hpp"
#include "xselectionslider.hpp"
#include "xtogglebuttons.hpp"
#include "xhtml.hpp"
#include "xbutton.hpp"
#include "xpassword.hpp"
#include "xlabel.hpp"
#include "xlayout.hpp"
#include "xprogress.hpp"
#include "xplay.hpp"
#include "xdropdown.hpp"
#include "xcolor_picker.hpp"
#include "xtogglebutton.hpp"
#include "xtext.hpp"
#include "xradiobuttons.hpp"
#include "xtab.hpp"
#include "xtextarea.hpp"
#include "xvalid.hpp"


namespace xw
{


    extern template class xmaterialize<xlabel>;
    extern template xmaterialize<xlabel>::xmaterialize();
    extern template class xtransport<xmaterialize<xlabel>>;
    extern template class xgenerator<xlabel>;
    extern template xgenerator<xlabel>::xgenerator();
    extern template class xtransport<xgenerator<xlabel>>;

    extern template class xmaterialize<xhtml>;
    extern template xmaterialize<xhtml>::xmaterialize();
    extern template class xtransport<xmaterialize<xhtml>>;
    extern template class xgenerator<xhtml>;
    extern template xgenerator<xhtml>::xgenerator();
    extern template class xtransport<xgenerator<xhtml>>;

    extern template class xmaterialize<xcheckbox>;
    extern template xmaterialize<xcheckbox>::xmaterialize();
    extern template class xtransport<xmaterialize<xcheckbox>>;
    extern template class xgenerator<xcheckbox>;
    extern template xgenerator<xcheckbox>::xgenerator();
    extern template class xtransport<xgenerator<xcheckbox>>;

    extern template class xmaterialize<xplay>;
    extern template xmaterialize<xplay>::xmaterialize();
    extern template class xtransport<xmaterialize<xplay>>;
    extern template class xgenerator<xplay>;
    extern template xgenerator<xplay>::xgenerator();
    extern template class xtransport<xgenerator<xplay>>;

    extern template class xmaterialize<xpassword>;
    extern template xmaterialize<xpassword>::xmaterialize();
    extern template class xtransport<xmaterialize<xpassword>>;
    extern template class xgenerator<xpassword>;
    extern template xgenerator<xpassword>::xgenerator();
    extern template class xtransport<xgenerator<xpassword>>;

    extern template class xmaterialize<xbutton_style>;
    extern template xmaterialize<xbutton_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xbutton_style>>;
    extern template class xgenerator<xbutton_style>;
    extern template xgenerator<xbutton_style>::xgenerator();
    extern template class xtransport<xgenerator<xbutton_style>>;

    extern template class xmaterialize<xbutton>;
    extern template xmaterialize<xbutton>::xmaterialize();
    extern template class xtransport<xmaterialize<xbutton>>;
    extern template class xgenerator<xbutton>;
    extern template xgenerator<xbutton>::xgenerator();
    extern template class xtransport<xgenerator<xbutton>>;

    extern template class xmaterialize<xdropdown>;
    extern template xmaterialize<xdropdown>::xmaterialize();
    extern template class xtransport<xmaterialize<xdropdown>>;
    extern template class xgenerator<xdropdown>;
    extern template xgenerator<xdropdown>::xgenerator();
    extern template class xtransport<xgenerator<xdropdown>>;

    extern template class xmaterialize<xselectionslider>;
    extern template xmaterialize<xselectionslider>::xmaterialize();
    extern template class xtransport<xmaterialize<xselectionslider>>;
    extern template class xgenerator<xselectionslider>;
    extern template xgenerator<xselectionslider>::xgenerator();
    extern template class xtransport<xgenerator<xselectionslider>>;

    extern template class xmaterialize<xselection_rangeslider>;
    extern template xmaterialize<xselection_rangeslider>::xmaterialize();
    extern template class xtransport<xmaterialize<xselection_rangeslider>>;
    extern template class xgenerator<xselection_rangeslider>;
    extern template xgenerator<xselection_rangeslider>::xgenerator();
    extern template class xtransport<xgenerator<xselection_rangeslider>>;

    extern template class xmaterialize<xprogress_style>;
    extern template xmaterialize<xprogress_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress_style>>;
    extern template class xgenerator<xprogress_style>;
    extern template xgenerator<xprogress_style>::xgenerator();
    extern template class xtransport<xgenerator<xprogress_style>>;

    
    extern template class xmaterialize<xprogress, int>;
    extern template xmaterialize<xprogress, int>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, int>>;
    extern template class xgenerator<xprogress, int>;
    extern template xgenerator<xprogress, int>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, int>>;
    
    extern template class xmaterialize<xprogress, float>;
    extern template xmaterialize<xprogress, float>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, float>>;
    extern template class xgenerator<xprogress, float>;
    extern template xgenerator<xprogress, float>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, float>>;
    
    extern template class xmaterialize<xprogress, double>;
    extern template xmaterialize<xprogress, double>::xmaterialize();
    extern template class xtransport<xmaterialize<xprogress, double>>;
    extern template class xgenerator<xprogress, double>;
    extern template xgenerator<xprogress, double>::xgenerator();
    extern template class xtransport<xgenerator<xprogress, double>>;
    

    extern template class xmaterialize<xcolor_picker>;
    extern template xmaterialize<xcolor_picker>::xmaterialize();
    extern template class xtransport<xmaterialize<xcolor_picker>>;
    extern template class xgenerator<xcolor_picker>;
    extern template xgenerator<xcolor_picker>::xgenerator();
    extern template class xtransport<xgenerator<xcolor_picker>>;

    extern template class xmaterialize<xtogglebuttons_style>;
    extern template xmaterialize<xtogglebuttons_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons_style>>;
    extern template class xgenerator<xtogglebuttons_style>;
    extern template xgenerator<xtogglebuttons_style>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebuttons_style>>;

    extern template class xmaterialize<xtogglebuttons>;
    extern template xmaterialize<xtogglebuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebuttons>>;
    extern template class xgenerator<xtogglebuttons>;
    extern template xgenerator<xtogglebuttons>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebuttons>>;

    extern template class xmaterialize<xlayout>;
    extern template xmaterialize<xlayout>::xmaterialize();
    extern template class xtransport<xmaterialize<xlayout>>;
    extern template class xgenerator<xlayout>;
    extern template xgenerator<xlayout>::xgenerator();
    extern template class xtransport<xgenerator<xlayout>>;

    extern template class xmaterialize<xtextarea>;
    extern template xmaterialize<xtextarea>::xmaterialize();
    extern template class xtransport<xmaterialize<xtextarea>>;
    extern template class xgenerator<xtextarea>;
    extern template xgenerator<xtextarea>::xgenerator();
    extern template class xtransport<xgenerator<xtextarea>>;

    extern template class xmaterialize<xtext>;
    extern template xmaterialize<xtext>::xmaterialize();
    extern template class xtransport<xmaterialize<xtext>>;
    extern template class xgenerator<xtext>;
    extern template xgenerator<xtext>::xgenerator();
    extern template class xtransport<xgenerator<xtext>>;

    extern template class xmaterialize<xhbox>;
    extern template xmaterialize<xhbox>::xmaterialize();
    extern template class xtransport<xmaterialize<xhbox>>;
    extern template class xgenerator<xhbox>;
    extern template xgenerator<xhbox>::xgenerator();
    extern template class xtransport<xgenerator<xhbox>>;

    extern template class xmaterialize<xvbox>;
    extern template xmaterialize<xvbox>::xmaterialize();
    extern template class xtransport<xmaterialize<xvbox>>;
    extern template class xgenerator<xvbox>;
    extern template xgenerator<xvbox>::xgenerator();
    extern template class xtransport<xgenerator<xvbox>>;

    extern template class xmaterialize<xslider_style>;
    extern template xmaterialize<xslider_style>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider_style>>;
    extern template class xgenerator<xslider_style>;
    extern template xgenerator<xslider_style>::xgenerator();
    extern template class xtransport<xgenerator<xslider_style>>;

    
    extern template class xmaterialize<xslider, int>;
    extern template xmaterialize<xslider, int>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, int>>;
    extern template class xgenerator<xslider, int>;
    extern template xgenerator<xslider, int>::xgenerator();
    extern template class xtransport<xgenerator<xslider, int>>;
    
    extern template class xmaterialize<xslider, float>;
    extern template xmaterialize<xslider, float>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, float>>;
    extern template class xgenerator<xslider, float>;
    extern template xgenerator<xslider, float>::xgenerator();
    extern template class xtransport<xgenerator<xslider, float>>;
    
    extern template class xmaterialize<xslider, double>;
    extern template xmaterialize<xslider, double>::xmaterialize();
    extern template class xtransport<xmaterialize<xslider, double>>;
    extern template class xgenerator<xslider, double>;
    extern template xgenerator<xslider, double>::xgenerator();
    extern template class xtransport<xgenerator<xslider, double>>;
    

    extern template class xmaterialize<xselect>;
    extern template xmaterialize<xselect>::xmaterialize();
    extern template class xtransport<xmaterialize<xselect>>;
    extern template class xgenerator<xselect>;
    extern template xgenerator<xselect>::xgenerator();
    extern template class xtransport<xgenerator<xselect>>;

    extern template class xmaterialize<xselect_multiple>;
    extern template xmaterialize<xselect_multiple>::xmaterialize();
    extern template class xtransport<xmaterialize<xselect_multiple>>;
    extern template class xgenerator<xselect_multiple>;
    extern template xgenerator<xselect_multiple>::xgenerator();
    extern template class xtransport<xgenerator<xselect_multiple>>;

    extern template class xmaterialize<xvalid>;
    extern template xmaterialize<xvalid>::xmaterialize();
    extern template class xtransport<xmaterialize<xvalid>>;
    extern template class xgenerator<xvalid>;
    extern template xgenerator<xvalid>::xgenerator();
    extern template class xtransport<xgenerator<xvalid>>;

    extern template class xmaterialize<xradiobuttons>;
    extern template xmaterialize<xradiobuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xradiobuttons>>;
    extern template class xgenerator<xradiobuttons>;
    extern template xgenerator<xradiobuttons>::xgenerator();
    extern template class xtransport<xgenerator<xradiobuttons>>;

    extern template class xmaterialize<xaccordion>;
    extern template xmaterialize<xaccordion>::xmaterialize();
    extern template class xtransport<xmaterialize<xaccordion>>;
    extern template class xgenerator<xaccordion>;
    extern template xgenerator<xaccordion>::xgenerator();
    extern template class xtransport<xgenerator<xaccordion>>;

    extern template class xmaterialize<xtab>;
    extern template xmaterialize<xtab>::xmaterialize();
    extern template class xtransport<xmaterialize<xtab>>;
    extern template class xgenerator<xtab>;
    extern template xgenerator<xtab>::xgenerator();
    extern template class xtransport<xgenerator<xtab>>;

    extern template class xmaterialize<xtogglebutton>;
    extern template xmaterialize<xtogglebutton>::xmaterialize();
    extern template class xtransport<xmaterialize<xtogglebutton>>;
    extern template class xgenerator<xtogglebutton>;
    extern template xgenerator<xtogglebutton>::xgenerator();
    extern template class xtransport<xgenerator<xtogglebutton>>;


}

#endif