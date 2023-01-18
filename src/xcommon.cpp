#include "xwidgets/xcommon.hpp"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "xeus/xinterpreter.hpp"
#include "xtarget.hpp"

namespace xw
{
    xcommon::xcommon()
        : m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(get_widget_target(), xeus::new_xguid())
    {
    }

    xcommon::~xcommon()
    {
    }

    xcommon::xcommon(xeus::xcomm&& comm)
        : m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(std::move(comm))
    {
    }

    xcommon::xcommon(const xcommon& other)
        : m_moved_from(false)
        , m_hold(nullptr)
        , m_comm(other.m_comm)
        , m_buffer_paths(other.m_buffer_paths)
    {
    }

    xcommon::xcommon(xcommon&& other)
        : m_moved_from(false)
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

    void xcommon::send_patch(nl::json&& patch, xeus::buffer_sequence&& buffers) const
    {
        // extract buffer paths
        auto paths = nl::json::array();
        extract_buffer_paths(buffer_paths(), patch, buffers, paths);

        // metadata
        nl::json metadata;
        metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

        // data
        nl::json data;
        data["method"] = "update";
        data["state"] = std::move(patch);
        data["buffer_paths"] = std::move(paths);

        // send
        m_comm.send(std::move(metadata), std::move(data), std::move(buffers));
    }

    void xcommon::open(nl::json&& patch, xeus::buffer_sequence&& buffers)
    {
        // extract buffer paths
        auto paths = nl::json::array();
        extract_buffer_paths(buffer_paths(), patch, buffers, paths);

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

    bool
    xcommon::same_patch(const std::string& name, const nl::json& j1, const xeus::buffer_sequence&, const nl::json& j2, const xeus::buffer_sequence&)
        const
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
