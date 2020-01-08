/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_BINARY_HPP
#define XWIDGETS_BINARY_HPP

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xeus/xmessage.hpp"

namespace nl = nlohmann;

namespace xw
{
    /****************
     * Declarations *
     ****************/

    using xjson_path_type = std::vector<std::string>;

    void extract_buffer_paths(const std::vector<xjson_path_type>& to_check,
                              const nl::json& patch,
                              const xeus::buffer_sequence& buffers,
                              nl::json& buffer_paths);

    void insert_buffer_paths(nl::json& patch,
                             const nl::json& buffer_paths);

    const std::string& xbuffer_reference_prefix();

    bool is_buffer_reference(const std::string& arg);

    int buffer_index(const std::string& v);

    /******************
     * Implementation *
     ******************/

    inline const std::string& xbuffer_reference_prefix()
    {
        static const std::string prefix = "@buffer_reference@";
        return prefix;
    }

    inline bool is_buffer_reference(const std::string& arg)
    {
        const std::string& prefix = xbuffer_reference_prefix();
        return arg.size() > prefix.size() &&
            std::equal(prefix.cbegin(), prefix.cend(), arg.cbegin());
    }

    inline int buffer_index(const std::string& v)
    {
        std::stringstream stream(v);
        stream.ignore(xbuffer_reference_prefix().size());
        int index = 0;
        stream >> index;
        return index;
    }

    namespace detail
    {
        inline const nl::json* get_buffers(const nl::json& patch,
                                           const xjson_path_type& path)
        {
            const nl::json* current = &patch;
            for (const auto& item : path)
            {
                if (current->is_array())
                {
                    current = &(*current)[std::stoul(item)];
                }
                else
                {
                    auto el = current->find(item);
                    if (el != current->end())
                    {
                        current = &(*el);
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
            return current;
        }

        inline nl::json* get_json(nl::json& patch, const xjson_path_type& path)
        {
            nl::json* current = &patch;
            for (const auto& item : path)
            {
                if (current->is_array())
                {
                    current = &(*current)[std::stoul(item)];
                }
                else
                {
                    current = &(*current)[item];
                }
            }
            return current;
        }

        template <class T>
        inline void set_json(nl::json& patch,
                             const xjson_path_type& path,
                             const T& value)
        {
            nl::json* json = get_json(patch, path);
            if (json != nullptr)
            {
                (*json) = value;
            }
        }

        inline void insert_buffer_path(nl::json& patch,
                                       const nl::json& path,
                                       std::size_t buffer_index)
        {
            xjson_path_type p = path;
            detail::set_json(patch, p,
                xbuffer_reference_prefix() + std::to_string(buffer_index));
        }
    }

    inline void extract_buffer_paths(const std::vector<xjson_path_type>& to_check,
                                     const nl::json& patch,
                                     const xeus::buffer_sequence& buffers,
                                     nl::json& buffer_paths)
    {
        buffer_paths = nl::json(buffers.size(), nullptr);
        for (const auto& path : to_check)
        {
            const nl::json* item = detail::get_buffers(patch, path);
            if (item != nullptr && item->is_string())
            {
                const std::string leaf = item->get<std::string>();
                if (is_buffer_reference(leaf))
                {
                    buffer_paths[buffer_index(leaf)] = path;
                }
            }
        }
    }

    inline void insert_buffer_paths(nl::json& patch,
                                    const nl::json& buffer_paths)
    {
        for (std::size_t i = 0; i != buffer_paths.size(); ++i)
        {
            detail::insert_buffer_path(patch, buffer_paths[i], i);
        }
    }
}

#endif
