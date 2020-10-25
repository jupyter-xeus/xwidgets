/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BINARY_HPP
#define XWIDGETS_BINARY_HPP

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xeus/xmessage.hpp"

#include "xwidgets_config.hpp"

namespace nl = nlohmann;

namespace xw
{
    using xjson_path_type = std::vector<std::string>;

    XWIDGETS_API void extract_buffer_paths(const std::vector<xjson_path_type>& to_check,
                                           const nl::json& patch,
                                           const xeus::buffer_sequence& buffers,
                                           nl::json& buffer_paths);

    XWIDGETS_API void insert_buffer_paths(nl::json& patch,
                                          const nl::json& buffer_paths);

    XWIDGETS_API const std::string& xbuffer_reference_prefix();

    XWIDGETS_API bool is_buffer_reference(const std::string& arg);

    XWIDGETS_API int buffer_index(const std::string& v);
}

#endif
