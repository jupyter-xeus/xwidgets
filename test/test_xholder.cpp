/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include <map>
#include <string>

#include "xwidgets/xbutton.hpp"

namespace xw
{
    TEST(xholder, adding_in_map)
    {
        std::map<std::string, xholder<xwidget>> hm;
        button b;
        b.description = "coincoin";
        hm["x"] = std::move(b);
        std::string res = hm["x"].template get<button>().description();
        ASSERT_EQ(b.description(), res);
    }
}