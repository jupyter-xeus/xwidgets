/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_FACTORY_HPP
#define XWIDGETS_FACTORY_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include <xeus/xcomm.hpp>

#include "xwidgets/xwidgets_config.hpp"

namespace nl = nlohmann;

namespace xw
{
    class XWIDGETS_API xfactory
    {
    public:

        using maker_type = std::function<void(xeus::xcomm&&, const nl::json&, const xeus::buffer_sequence&)>;

        void register_maker(
            const std::string& model_module,
            const std::string& model_name,
            const std::string& view_module,
            const std::string& view_name,
            maker_type maker
        );

        void make(xeus::xcomm&& comm, const nl::json& state, const xeus::buffer_sequence&) const;

    private:

        std::unordered_map<std::string, maker_type> m_makers;
    };

    XWIDGETS_API xfactory& get_xfactory();
}

#endif
