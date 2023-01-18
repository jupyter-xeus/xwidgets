/***************************************************************************
 * Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include <map>
#include <string>

#include "doctest/doctest.h"
#include "xwidgets/xbutton.hpp"

namespace xw
{

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

        int value() const
        {
            return m_value;
        }

        static int instance_count()
        {
            return m_instance_count;
        }

    private:

        int m_value;
        static int m_instance_count;
    };

    int button_tester::m_instance_count = 0;

    TEST_SUITE("xholder")
    {
        TEST_CASE("adding_in_map")
        {
            std::map<std::string, xholder> hm;
            button b;
            std::string desc = "coincoin";
            b.description = desc;
            hm["x"] = std::move(b);
            std::string res = hm["x"].template get<button>().description();
            REQUIRE_EQ(desc, res);
        }

        TEST_CASE("shared")
        {
            using map_type = std::map<std::string, xholder>;
            map_type hm1, hm2;
            hm1["x"] = make_shared_holder<button_tester>(std::make_shared<button_tester>());
            hm2["x"] = hm1["x"];
            REQUIRE_EQ(hm1["x"].id(), hm2["x"].id());
            REQUIRE_EQ(button_tester::instance_count(), 1);

            hm1["y"] = make_shared_holder<button_tester>(std::make_shared<button_tester>(4));
            hm2["y"] = hm1["y"];
            REQUIRE_EQ(
                hm1["y"].template get<button_tester>().value(),
                hm2["y"].template get<button_tester>().value()
            );
            REQUIRE_EQ(button_tester::instance_count(), 2);

            hm1.erase("x");
            REQUIRE_EQ(button_tester::instance_count(), 2);
            hm2.erase("x");
            REQUIRE_EQ(button_tester::instance_count(), 1);

            hm1.erase("y");
            REQUIRE_EQ(button_tester::instance_count(), 1);
            hm2.erase("y");
            REQUIRE_EQ(button_tester::instance_count(), 0);
        }

        TEST_CASE("constructor")
        {
            using holder = xholder;
            button b1, b2;
            auto b3 = std::make_shared<button>();

            holder h1(b1);
            holder h2(std::move(b2));
            holder h3(b3);

            button b11, b22;
            auto b33 = std::make_shared<button>();

            h1 = b11;
            h2 = std::move(b22);
            h3 = b33;
        }
    }
}
