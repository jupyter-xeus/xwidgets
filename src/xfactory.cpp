/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xfactory.hpp"

#include <utility>

namespace nl = nlohmann;

namespace xw
{
    void xfactory::register_maker(
        const std::string& model_module,
        const std::string& model_name,
        const std::string& view_module,
        const std::string& view_name,
        maker_type maker
    )
    {
        m_makers[model_module + model_name + view_module + view_name] = std::move(maker);
    }

    void xfactory::make(xeus::xcomm&& comm, const nl::json& state, const xeus::buffer_sequence& buffers) const
    {
        std::string model_module = state["_model_module"];
        std::string model_name = state["_model_name"];
        std::string view_module = state["_view_module"];
        std::string view_name = state["_view_name"];
        m_makers.at(model_module + model_name + view_module + view_name)(std::move(comm), state, buffers);
    }

    xfactory& get_xfactory()
    {
        static xfactory factory;
        return factory;
    }
}
