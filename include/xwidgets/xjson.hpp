/***************************************************************************
 * Copyright (c) 2024, QuantStack                                           *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_JSON_HPP
#define XWIDGETS_JSON_HPP

#include <optional>

#include <nlohmann/json.hpp>

namespace nlohmann
{
    template <class T>
    struct adl_serializer<std::optional<T>>
    {
        static void to_json(nlohmann::json& j, const std::optional<T>& o)
        {
            if (!o.has_value())
            {
                j = nullptr;
            }
            else
            {
                j = o.value();
            }
        }

        static void from_json(const nlohmann::json& j, std::optional<T>& o)
        {
            if (j.is_null())
            {
                o = std::nullopt;
            }
            else
            {
                o = j.get<T>();
            }
        }
    };
}

#endif
