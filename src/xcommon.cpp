/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include "xwidgets/xcommon.hpp"

#include <algorithm>
#include <cstdlib>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "xeus/xinterpreter.hpp"
#include "xtarget.hpp"

namespace xw
{
    xcommon::xcommon()
        : observed_type()
        , m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(get_widget_target(), xeus::new_xguid())
    {
    }

    xcommon::~xcommon()
    {
    }

    xcommon::xcommon(xeus::xcomm&& comm)
        : observed_type()
        , m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(std::move(comm))
    {
    }

    xcommon::xcommon(const xcommon& other)
        : observed_type()
        , m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(other.m_comm)
        , m_buffer_paths(other.m_buffer_paths)
    {
    }

    xcommon::xcommon(xcommon&& other)
        : observed_type()
        , m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(std::move(other.m_comm))
        , m_buffer_paths(std::move(other.m_buffer_paths))
    {
        other.m_moved_from = true;
    }

    xcommon& xcommon::operator=(const xcommon& other)
    {
        m_moved_from = false;
        m_hold = nullptr;
        m_comm = other.m_comm;
        m_buffer_paths = other.m_buffer_paths;
        return *this;
    }

    xcommon& xcommon::operator=(xcommon&& other)
    {
        other.m_moved_from = true;
        m_moved_from = false;
        m_hold = nullptr;
        m_comm = std::move(other.m_comm);
        m_buffer_paths = std::move(other.m_buffer_paths);
        return *this;
    }

    auto xcommon::id() const noexcept -> xeus::xguid
    {
        return m_comm.id();
    }

    void xcommon::display() const
    {
        nl::json mime_bundle;

        // application/vnd.jupyter.widget-view+json
        nl::json widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = this->id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget";

        ::xeus::get_interpreter().display_data(std::move(mime_bundle), nl::json::object(), nl::json::object());
    }

    void xcommon::send(nl::json&& content, xeus::buffer_sequence&& buffers) const
    {
        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["method"] = "custom";
        data["content"] = std::move(content);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    void xcommon::handle_custom_message(const nl::json& /*content*/)
    {
    }

    xeus::xcomm& xcommon::comm()
    {
        return m_comm;
    }

    const xeus::xcomm& xcommon::comm() const
    {
        return m_comm;
    }

    const xeus::xmessage*& xcommon::hold()
    {
        return m_hold;
    }

    const xeus::xmessage* const& xcommon::hold() const
    {
        return m_hold;
    }

    bool xcommon::moved_from() const noexcept
    {
        return m_moved_from;
    }

    std::vector<xjson_path_type>& xcommon::buffer_paths()
    {
        return m_buffer_paths;
    }

    const std::vector<xjson_path_type>& xcommon::buffer_paths() const
    {
        return m_buffer_paths;
    }

    void xcommon::send_patch(nl::json&& patch, xeus::buffer_sequence&& buffers, const char* method) const
    {
        // extract buffer paths
        std::vector<nl::json> paths{};
        reorder_buffer_paths(buffer_paths(), patch, paths);

        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["method"] = method;
        data["state"] = std::move(patch);
        data["buffer_paths"] = std::move(paths);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    void xcommon::open(nl::json&& patch, xeus::buffer_sequence&& buffers)
    {
        // extract buffer paths
        std::vector<nl::json> paths{};
        reorder_buffer_paths(buffer_paths(), patch, paths);

        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;

        data["state"] = std::move(patch);
        data["buffer_paths"] = std::move(paths);

        // open
        m_comm.open(std::move(metadata), std::move(data), std::move(buffers));
    }

    void xcommon::close()
    {
        // close
        m_comm.close(nl::json::object(), nl::json::object(), xeus::buffer_sequence());
    }

    namespace
    {
        std::string tolower(std::string s)
        {
            auto safe_tolower = [](unsigned char c)
            {
                return std::tolower(c);
            };
            std::transform(s.begin(), s.end(), s.begin(), safe_tolower);
            return s;
        }

        std::string ltrim(std::string s)
        {
            auto const safe_isnotspace = [](unsigned char ch)
            {
                return !std::isspace(ch);
            };
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), safe_isnotspace));
            return s;
        }

        std::string rtrim(std::string s)
        {
            auto const safe_isnotspace = [](unsigned char ch)
            {
                return !std::isspace(ch);
            };
            s.erase(std::find_if(s.rbegin(), s.rend(), safe_isnotspace).base(), s.end());
            return s;
        }

        std::string trim(std::string s)
        {
            rtrim(s);
            ltrim(s);
            return s;
        }

        bool is_zero_number(std::string const& s)
        {
            try
            {
                auto val = std::stod(s);
                return val == decltype(val)(0);
            }
            catch (std::invalid_argument const&)
            {
                return false;
            }
            catch (std::out_of_range const&)
            {
                return false;
            }
        }

        /**
         * Check if a string is true.
         *
         * A string is true, if it does not contain a negative value, such as "false" or 0.
         * This is the convention adopted in Jupyter
         * https://github.com/jupyter/jupyter_core/blob/98ab1ef453956333a85bb6eee494ad0a9bab2c02/jupyter_core/paths.py#L47
         */
        bool is_true_string(const char* str)
        {
            const std::string s = tolower(trim(str));
            if (is_zero_number(str))
            {
                return false;
            }
            static constexpr auto falses = {"no", "n", "false", "off"};
            return std::find(falses.begin(), falses.end(), s) == falses.end();
        }

        std::optional<bool> get_tristate_env(const char* name)
        {
            const char* const val = std::getenv(name);
            if (val == nullptr)
            {
                return {};
            }
            return is_true_string(val);
        }
    }

    std::optional<bool> xcommon::global_echo_update()
    {
        static const auto out = get_tristate_env("JUPYTER_WIDGETS_ECHO");
        return out;
    }

    bool xcommon::same_patch(
        const std::string& name,
        const nl::json& j1,
        const xeus::buffer_sequence&,
        const nl::json& j2,
        const xeus::buffer_sequence&
    ) const
    {
        const auto& paths = buffer_paths();
        // For a widget with no binary buffer, compare the patches
        if (paths.empty())
        {
            return j1 == j2;
        }
        else
        {
            // For a property with no binary buffer, compare the patches
            if (std::find_if(
                    paths.cbegin(),
                    paths.cend(),
                    [name](const auto& v)
                    {
                        return !v.empty() && v[0] == name;
                    }
                )
                == paths.cend())
            {
                return j1 == j2;
            }
            else
            {
                // TODO: handle the comparison of binary buffers.
                return true;
            }
        }
    }

    void xcommon::register_patch_applier(const std::string& name, patch_applier_type&& applier)
    {
        m_patch_appliers[name] = std::move(applier);
    }

    void
    xcommon::apply_patch_to_registered_properties(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        for (auto it = patch.begin(); it != patch.end(); ++it)
        {
            const auto& key = it.key();
            auto applier_it = m_patch_appliers.find(key);
            if (applier_it != m_patch_appliers.end())
            {
                applier_it->second(*it, buffers);
            }
        }
    }

    void to_json(nl::json& j, const xcommon& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    nl::json mime_bundle_repr(const xcommon& val)
    {
        nl::json mime_bundle;

        // application/vnd.jupyter.widget-view+json
        nl::json widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = val.id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget with unique id: " + std::string(val.id());
        return mime_bundle;
    }
}
