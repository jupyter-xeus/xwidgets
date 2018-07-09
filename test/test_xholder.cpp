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
        std::string desc = "coincoin";
        b.description = desc;
        hm["x"] = std::move(b);
        std::string res = hm["x"].template get<button>().description();
        ASSERT_EQ(desc, res);
    }

    class button_tester : public xwidget<button_tester>
    {
    public:

        button_tester(int value = 0)
            : m_value(value)
        {
            ++m_instance_count;
        }

        ~button_tester()
        {
            --m_instance_count;
        }

        button_tester(const button_tester& rhs)
            : m_value(rhs.m_value)
        {
            ++m_instance_count;
        }

        button_tester(button_tester&& rhs)
            : m_value(rhs.m_value)
        {
            ++m_instance_count;
        }

        button_tester& operator=(const button_tester&) = default;
        button_tester& operator=(button_tester&&) = default;

        int value() const { return m_value; }

        static int instance_count() { return m_instance_count; }

    private:

        int m_value;
        static int m_instance_count;
    };

    int button_tester::m_instance_count = 0;

    TEST(xholder, shared)
    {
        using map_type = std::map<std::string, xholder<xwidget>>;
        map_type hm1, hm2;
        button_tester* b = new button_tester;
        hm1["x"] = make_shared_holder<xwidget>(b);
        hm2["x"] = hm1["x"];
        ASSERT_EQ(hm1["x"].id(), hm2["x"].id());
        ASSERT_EQ(button_tester::instance_count(), 1);

        hm1["y"] = make_shared_holder<xwidget, button_tester>(4);;
        hm2["y"] = hm1["y"];
        ASSERT_EQ(hm1["y"].template get<button_tester>().value(), hm2["y"].template get<button_tester>().value());
        ASSERT_EQ(button_tester::instance_count(), 2);

        hm1.erase("x");
        ASSERT_EQ(button_tester::instance_count(), 2);
        hm2.erase("x");
        ASSERT_EQ(button_tester::instance_count(), 1);

        hm1.erase("y");
        ASSERT_EQ(button_tester::instance_count(), 1);
        hm2.erase("y");
        ASSERT_EQ(button_tester::instance_count(), 0);
    }
}