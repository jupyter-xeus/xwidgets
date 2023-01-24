/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_ALL_HPP
#define XWIDGETS_ALL_HPP

#include <tuple>

#include "xaccordion.hpp"
#include "xaudio.hpp"
#include "xbinary.hpp"
#include "xboolean.hpp"
#include "xbox.hpp"
#include "xbutton.hpp"
#include "xcheckbox.hpp"
#include "xcolor.hpp"
#include "xcolor_picker.hpp"
#include "xcommon.hpp"
#include "xcontroller.hpp"
#include "xdescription_style.hpp"
#include "xdropdown.hpp"
#include "xhtml.hpp"
#include "ximage.hpp"
#include "xlabel.hpp"
#include "xlayout.hpp"
#include "xlink.hpp"
#include "xmedia.hpp"
#include "xnumber.hpp"
#include "xnumeral.hpp"
#include "xoutput.hpp"
#include "xpassword.hpp"
#include "xplay.hpp"
#include "xprogress.hpp"
#include "xradiobuttons.hpp"
#include "xselect.hpp"
#include "xselection.hpp"
#include "xselectionslider.hpp"
#include "xslider.hpp"
#include "xtab.hpp"
#include "xtext.hpp"
#include "xtextarea.hpp"
#include "xtogglebutton.hpp"
#include "xtogglebuttons.hpp"
#include "xvalid.hpp"
#include "xvideo.hpp"

namespace xw
{
    using AllWidgets = std::tuple<
        accordion,
        audio,
        button,
        checkbox,
        color_picker,
        controller,
        controller_axis,
        controller_button,
        directional_link,
        dropdown,
        hbox,
        html,
        image,
        label,
        layout,
        link,
        media,
        number<int>,
        number<float>,
        number<double>,
        numeral<int>,
        numeral<float>,
        numeral<double>,
        output,
        password,
        play,
        progress<int>,
        progress<float>,
        progress<double>,
        radiobuttons,
        select,
        select_multiple,
        selection_rangeslider,
        selectionslider,
        slider<int>,
        slider<float>,
        slider<double>,
        tab,
        text,
        textarea,
        togglebutton,
        togglebuttons,
        valid,
        vbox,
        video>;

    using AllStyles = std::tuple<
        button_style,
        checkbox_style,
        description_style,
        html_style,
        progress_style,
        slider_style,
        text_style,
        togglebutton_style,
        togglebuttons_style>;

}

#endif
