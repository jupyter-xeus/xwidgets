/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xwidgets/xslider.hpp"

namespace xeus
{
    TEST(xslider, basic)
    {
        xslider<double> slider;
        slider.value = 2.0;
        ASSERT_EQ(2., slider.value());
    }
}

