/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_EITHER_HPP
#define XWIDGETS_EITHER_HPP

#include <stdexcept>
#include <string>
#include <unordered_set>

#include "xtl/xoptional.hpp"

namespace xw
{
    namespace detail
    {
        // TODO: use xtl::has_value in xtl >= 0.3.5

        template <class T, class U = xtl::disable_xoptional<std::decay_t<T>>>
        T&& value(T&& v)
        {
            return std::forward<T>(v);
        }

        template <class CT, class CB>
        decltype(auto) value(xtl::xoptional<CT, CB>&& v)
        {
            return std::move(v).value();
        }
 
        template <class CT, class CB>
        decltype(auto) value(xtl::xoptional<CT, CB>& v)
        {
            return v.value();
        }
 
        template <class CT, class CB>
        decltype(auto) value(const xtl::xoptional<CT, CB>& v)
        {
            return v.value();
        }
 
        // has_value
 
        template <class T, class U = xtl::disable_xoptional<std::decay_t<T>>>
        bool has_value(T&&)
        {
            return true;
        }
 
        template <class CT, class CB>
        decltype(auto) has_value(xtl::xoptional<CT, CB>&& v)
        {
            return std::move(v).has_value();
        }
 
        template <class CT, class CB>
        decltype(auto) has_value(xtl::xoptional<CT, CB>& v)
        {
            return std::move(v).has_value();
        }
 
        template <class CT, class CB>
        decltype(auto) has_value(const xtl::xoptional<CT, CB>& v)
        {
            return std::move(v).has_value();
        }
    }
}

#define XEITHER(...)                                                       \
 [](const auto& proposal) {                                                \
     static const std::unordered_set<std::string> options({__VA_ARGS__});  \
     auto position = options.find(proposal);                               \
     if (position == options.end())                                        \
     {                                                                     \
         throw std::runtime_error("Invalid proposal for string enum");     \
     }                                                                     \
 }

#define XEITHER_OPTIONAL(...)                                                       \
 [](const auto& proposal) {                                                         \
     if (xw::detail::has_value(proposal))                                           \
     {                                                                              \
         static const std::unordered_set<std::string> options({__VA_ARGS__});       \
         auto position = options.find(xw::detail::value(proposal));                 \
         if (position == options.end())                                             \
         {                                                                          \
             throw std::runtime_error("Invalid proposal for optional string enum"); \
         }                                                                          \
     }                                                                              \
 }


#endif
