/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xwidgets/xbox.hpp"
#include "xwidgets/xbutton.hpp"
#include "xwidgets/xcheckbox.hpp"
#include "xwidgets/xhtml.hpp"
#include "xwidgets/xlabel.hpp"
#include "xwidgets/xlayout.hpp"
#include "xwidgets/xnumeral.hpp"
#include "xwidgets/xpassword.hpp"
#include "xwidgets/xplay.hpp"
#include "xwidgets/xprogress.hpp"
#include "xwidgets/xslider.hpp"
#include "xwidgets/xtext.hpp"
#include "xwidgets/xtextarea.hpp"
#include "xwidgets/xtogglebutton.hpp"
#include "xwidgets/xvalid.hpp"

namespace xw
{
    TEST(xwidgets, box)
    {
        hbox hb;
        slider<double> s1, s2, s3;
        hb.add(s1);
        hb.add(s2);
        hb.add(s3);
        ASSERT_EQ(3u, hb.children().size());
        hb.remove(s1);
        ASSERT_EQ(2u, hb.children().size());
        hb.clear();
        ASSERT_EQ(0u, hb.children().size());
    }

    TEST(xwidgets, hbox)
    {
        hbox hb;
        slider<double> s1, s2;
        hb.add(s1);
        hb.add(s2);

        auto s3 = std::make_shared<slider<double>>();
        hb.add(s3);
    }

    TEST(xwidgets, vbox)
    {
        vbox vb;
        slider<double> s1, s2;
        vb.add(s1);
        vb.add(s2);

        auto s3 = std::make_shared<slider<double>>();
        vb.add(s3);
    }

    TEST(xwidgets, button_style)
    {
        button_style bs;
        bs.button_color = "red";
        bs.font_weight = "10";
        ASSERT_EQ("red", bs.button_color());
        ASSERT_EQ("10", bs.font_weight());
    }

    TEST(xwidgets, button)
    {
        button b;
        b.tooltip = "tooltip";
        b.disabled = true;
        b.icon = "icon";
        ASSERT_EQ("tooltip", b.tooltip());
        ASSERT_EQ(true, b.disabled());
        ASSERT_EQ("icon", b.icon());
    }

    TEST(xwidgets, checkbox)
    {
        checkbox c;
        c.indent = true;
        ASSERT_EQ(true, c.indent());
    }

    TEST(xwidgets, html)
    {
        html h;
        h.description = "description";
        ASSERT_EQ("description", h.description());
    }

    TEST(xwidgets, label)
    {
        label l;
        l.description = "description";
        ASSERT_EQ("description", l.description());
    }

    TEST(xwidgets, layout)
    {
        layout l;
        l.bottom = "bottom";
        ASSERT_EQ("bottom", l.bottom());
    }

    TEST(xwidgets, numeral)
    {
        numeral<double> n;
        n.value = 12.;
        ASSERT_EQ(12., n.value());
    }

    TEST(xwidgets, password)
    {
        password p;
        p.description = "description";
        ASSERT_EQ("description", p.description());
    }

    TEST(xwidgets, play)
    {
        play p;
        p.interval = 15;
        ASSERT_EQ(15, p.interval());
    }

    TEST(xwidgets, progress_style)
    {
        progress_style p;
        p.description_width = "40px";
        ASSERT_EQ("40px", p.description_width());
    }

    TEST(xwidgets, progress)
    {
        progress<double> p;
        p.orientation = "vertical";
        ASSERT_EQ("vertical", p.orientation());
    }

    TEST(xwidgets, slider_style)
    {
        slider_style s;
        s.description_width = "40px";
        ASSERT_EQ("40px", s.description_width());
    }

    TEST(xwidgets, slider)
    {
        slider<double> s;
        s.value = 2.0;
        ASSERT_EQ(2., s.value());
    }

    TEST(xwidgets, text)
    {
        text t;
        t.disabled = true;
        ASSERT_EQ(true, t.disabled());
    }

    TEST(xwidgets, textarea)
    {
        textarea t;
        t.disabled = true;
        ASSERT_EQ(true, t.disabled());
    }

    TEST(xwidgets, togglebutton)
    {
        togglebutton t;
        t.tooltip = "tooltip";
        ASSERT_EQ("tooltip", t.tooltip());
    }

    TEST(xwidgets, valid)
    {
        valid v;
        v.readout = "readout";
        ASSERT_EQ("readout", v.readout());
    }
}
