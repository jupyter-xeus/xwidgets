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

template <typename ... T>
auto XEITHER(T... vals)	{			\
  const std::unordered_set<std::string> options({vals...});
  return [options](const auto& proposal) {
	   auto position = options.find(proposal);
	   if (position == options.end()) {
            throw std::runtime_error("Invalid proposal for string enum");
	   }					\
	 };
}

template <typename ... T>
auto XEITHER_OPTIONAL(T...vals) {
    const std::unordered_set<std::string> options({vals...});
    return [options](const auto& proposal) {
	     if (xtl::has_value(proposal)) {
	       auto position = options.find(xtl::value(proposal));
	       if (position == options.end()) {
		 throw std::runtime_error("Invalid proposal for optional string enum");
	       }
	     }
	   };
}

#endif
