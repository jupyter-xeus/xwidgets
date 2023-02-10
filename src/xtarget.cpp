/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xtarget.hpp"

#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include <nlohmann/json.hpp>
#include <xeus/xcomm.hpp>
#include <xeus/xinterpreter.hpp>

#include "xwidgets/xbinary.hpp"
#include "xwidgets/xcommon.hpp"
#include "xwidgets/xfactory.hpp"
#include "xwidgets/xregistry.hpp"
#include "xwidgets/xwidgets_config.hpp"

namespace xw
{
    namespace
    {
        const char* get_widget_target_name()
        {
            return "jupyter.widget";
        }

        /**
         * Check frontend widget version and instanciate widget.
         *
         * This callback function is called by Xeus when a comm channel is open by the frontend
         * to create a companion widget in the kernel.
         */
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
                /** The target name */
                get_widget_target_name(),
                /** Callback for comm opened by the frontend on this target, one per widget */
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

    namespace
    {
        template <typename JsonPath>
        std::vector<xjson_path_type>
        prepend_to_json_paths(std::vector<xjson_path_type> paths, JsonPath const& prefix)
        {
            std::for_each(
                paths.begin(),
                paths.end(),
                [&](xjson_path_type& p)
                {
                    p.insert(p.begin(), prefix.begin(), prefix.end());
                }
            );
            return paths;
        }

        void
        serialize_all_states(nl::json& states, xeus::buffer_sequence& buffers, std::vector<nl::json>& buffer_paths)
        {
            for (auto const& id_and_widget : get_transport_registry())
            {
                auto const& holder = id_and_widget.second;
                // This is not what the protocol states (?) but what IPyWidgets does
                // https://github.com/jupyter-widgets/ipywidgets/issues/3685
                nl::json stateish = nl::json::object();
                holder.serialize_state(stateish["state"], buffers);
                stateish["model_name"] = stateish["state"]["_model_name"];
                stateish["model_module"] = stateish["state"]["_model_module"];
                stateish["model_module_version"] = stateish["state"]["_model_module_version"];
                states[holder.id()] = std::move(stateish);
                // Add buffer paths, but add the xguid/state prefix of multi-state schema
                reorder_buffer_paths(
                    prepend_to_json_paths(holder.buffer_paths(), std::array<std::string, 2>{holder.id(), "state"}),
                    states,
                    buffer_paths
                );
            }
        }

        /**
         * Register the ``on_message`` callback on the comm to get all widgets states.
         *
         * This callback function is called by Xeus when a comm channel is open by the frontend
         * on the ``jupyter.widget.control`` target.
         * This happens when the frontend needs to get the state of all widgets and no immediate
         * action is required.
         * Following the opening of the comm, the frontend sends a message with a
         * ``request_states`` method, to which the kernel replies with the state of all widgets.
         *
         * After the frontend recieves the ``update_states`` response it closes the comm.
         * Additional (and simulataneous) comms can be opened for fetching states.
         */
        void control_comm_opened(xeus::xcomm&& comm, const xeus::xmessage&)
        {
            // This is a very simple registry for comm since their lifetime is managed by the
            // frontend
            static std::unordered_map<xeus::xguid, xeus::xcomm> comm_registry{};

            auto iter_inserted = comm_registry.emplace(std::make_pair(comm.id(), std::move(comm)));
            // Should really be inserted, but in case it is not, we let the comm gets destroyed and closed
            assert(iter_inserted.second);
            if (!iter_inserted.second)
            {
                return;
            }

            auto& registered_comm = iter_inserted.first->second;

            registered_comm.on_message(
                [&](const ::xeus::xmessage& msg)
                {
                    auto const& method = msg.content()["data"]["method"];

                    nl::json states = nl::json::object();
                    xeus::buffer_sequence buffers{};
                    std::vector<nl::json> buffer_paths{};
                    serialize_all_states(states, buffers, buffer_paths);

                    nl::json metadata = {{"version", XWIDGETS_PROTOCOL_VERSION}};

                    nl::json data = nl::json::object();
                    data["method"] = "update_states";
                    data["states"] = std::move(states);
                    data["buffer_paths"] = std::move(buffer_paths);

                    registered_comm.send(std::move(metadata), std::move(data), std::move(buffers));
                }
            );

            registered_comm.on_close(
                [&](const ::xeus::xmessage&)
                {
                    // This is not trivial. The comm is destructed from within one of its method.
                    // This works because no other instruction are executed by Xeus afterwards.
                    comm_registry.erase(registered_comm.id());
                }
            );
        }

        const char* get_control_target_name()
        {
            return "jupyter.widget.control";
        }

        /**
         * Register the ``jupyter.widget.control`` Xeus target.
         *
         * This target is used by the frontend to get the state of all widget in a single message
         * (_e.g._ when restarting).
         */
        void register_control_target()
        {
            xeus::get_interpreter().comm_manager().register_comm_target(
                /** The target name */
                get_control_target_name(),
                /** Callback for comm opened by the frontend on this target */
                control_comm_opened
            );
        }

        // Making a dummy static variable to call the registration at load time.
        static const auto initialized = []()
        {
            register_control_target();
            return true;
        }();
    }
}
