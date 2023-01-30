/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xtarget.hpp"

#include <stdexcept>
#include <string>
#include <utility>

#include <xeus/xcomm.hpp>
#include <xeus/xinterpreter.hpp>

#include "xwidgets/xfactory.hpp"
#include "xwidgets/xwidgets_config.hpp"

namespace xw
{
    namespace
    {
        const char* get_widget_target_name()
        {
            return "jupyter.widget";
        }

        void xobject_comm_opened(xeus::xcomm&& comm, const xeus::xmessage& msg)
        {
            const nl::json& content = msg.content();
            const nl::json& metadata = msg.metadata();

            std::string version;
            try
            {
                version = metadata.at("version").get<std::string>();
            }
            catch (std::out_of_range const&)
            {
                version = "";
            }

            if (version.substr(0, version.find(".")) != XWIDGETS_STRINGIFY(XWIDGETS_PROTOCOL_VERSION_MAJOR))
            {
                throw std::runtime_error("Incompatible widget protocol versions");
            }

            const nl::json& data = content["data"];
            const nl::json& state = data["state"];
            const xeus::buffer_sequence& buffers = msg.buffers();

            xfactory& factory = get_xfactory();
            factory.make(std::move(comm), state, buffers);
        }

        void register_widget_target()
        {
            xeus::get_interpreter().comm_manager().register_comm_target(
                get_widget_target_name(),
                xobject_comm_opened
            );
        }
    }

    xeus::xtarget* get_widget_target()
    {
        // Making a dummy static variable to only call the registration once.
        static const auto initialized = []()
        {
            register_widget_target();
            return true;
        }();
        return ::xeus::get_interpreter().comm_manager().target(get_widget_target_name());
    }
}
