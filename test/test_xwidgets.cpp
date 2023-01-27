/***************************************************************************
 * Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include <doctest/doctest.h>

#include "xwidgets/xall.hpp"

namespace xw
{
    TEST_SUITE("xwidgets")
    {
        TEST_CASE("box")
        {
            hbox hb;
            slider<double> s1, s2, s3;
            hb.add(s1);
            hb.add(s2);
            hb.add(s3);
            REQUIRE_EQ(3u, hb.children().size());
            hb.remove(s1);
            REQUIRE_EQ(2u, hb.children().size());
            hb.clear();
            REQUIRE_EQ(0u, hb.children().size());
        }

        TEST_CASE("hbox")
        {
            hbox hb;
            slider<double> s1, s2;
            hb.add(s1);
            hb.add(s2);

            auto s3 = std::make_shared<slider<double>>();
            hb.add(s3);
        }

        TEST_CASE("vbox")
        {
            vbox vb;
            slider<double> s1, s2;
            vb.add(s1);
            vb.add(s2);

            auto s3 = std::make_shared<slider<double>>();
            vb.add(s3);
        }

        TEST_CASE("button_style")
        {
            button_style bs;
            bs.button_color = "red";
            bs.font_weight = "10";
            REQUIRE_EQ("red", bs.button_color());
            REQUIRE_EQ("10", bs.font_weight());
        }

        TEST_CASE("button")
        {
            button b;
            b.tooltip = "tooltip";
            b.disabled = true;
            b.icon = "icon";
            REQUIRE_EQ("tooltip", b.tooltip());
            REQUIRE_EQ(true, b.disabled());
            REQUIRE_EQ("icon", b.icon());
        }

        TEST_CASE("checkbox")
        {
            checkbox c;
            c.indent = true;
            REQUIRE_EQ(true, c.indent());
        }

        TEST_CASE("checkbox.style")
        {
            checkbox c;
            c.style = checkbox_style::initialize()  //
                          .background("black")
                          .description_width("3")
                          .finalize();
            REQUIRE_EQ("black", c.style().background());
            REQUIRE_EQ("3", c.style().description_width());

            c.style().description_width = "50";
            REQUIRE_EQ("50", c.style().description_width());
        }

        TEST_CASE("html")
        {
            html h;
            h.description = "description";
            REQUIRE_EQ("description", h.description());
        }

        TEST_CASE("label")
        {
            label l;
            l.description = "description";
            REQUIRE_EQ("description", l.description());
        }

        TEST_CASE("layout")
        {
            layout l;
            l.bottom = "bottom";
            REQUIRE_EQ("bottom", l.bottom());
        }

        TEST_CASE("number")
        {
            number<double> n;
            n.value = 12.;
            REQUIRE_EQ(12., n.value());
        }

        TEST_CASE("number_bounded")
        {
            number_bounded<double> n;
            n.max = 10.;
            n.value = n.max() + 1.;
            REQUIRE_EQ(n.max(), n.value());
        }

        TEST_CASE("password")
        {
            password p;
            p.description = "description";
            REQUIRE_EQ("description", p.description());
        }

        TEST_CASE("play")
        {
            play p;
            p.interval = 15;
            REQUIRE_EQ(15, p.interval());
        }

        TEST_CASE("progress_style")
        {
            progress_style p;
            p.description_width = "40px";
            REQUIRE_EQ("40px", p.description_width());
        }

        TEST_CASE("progress")
        {
            progress<double> p;
            p.orientation = "vertical";
            REQUIRE_EQ("vertical", p.orientation());
        }

        TEST_CASE("slider_style")
        {
            slider_style s;
            s.description_width = "40px";
            REQUIRE_EQ("40px", s.description_width());
        }

        TEST_CASE("slider")
        {
            slider<double> s;
            s.value = 2.0;
            REQUIRE_EQ(2., s.value());
        }

        TEST_CASE("text")
        {
            text t;
            t.disabled = true;
            REQUIRE_EQ(true, t.disabled());
        }

        TEST_CASE("textarea")
        {
            textarea t;
            t.disabled = true;
            REQUIRE_EQ(true, t.disabled());
        }

        TEST_CASE("togglebutton")
        {
            togglebutton t;
            t.tooltip = "tooltip";
            REQUIRE_EQ("tooltip", t.tooltip());
        }

        TEST_CASE("valid")
        {
            valid v;
            v.readout = "readout";
            REQUIRE_EQ("readout", v.readout());
        }
    }
}
