#include "xwidgets/xtransport.hpp"

namespace xw
{
  void xtransport_base::finalize_open(xeus::xcomm & comm, nl::json && paths,
                                      nl::json && state,
                                      xeus::buffer_sequence && buffers) {
    // metadata
    nl::json metadata;
    metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

    // data
    nl::json data;
    data["state"] = std::move(state);
    data["buffer_paths"] = std::move(paths);

    comm.open(std::move(metadata), std::move(data), std::move(buffers));
  }

  void xtransport_base::finalize_close(xeus::xcomm & comm) {
    comm.close(nl::json::object(), nl::json::object(), xeus::buffer_sequence());
  }

  bool xtransport_base::finalize_same_patch(
      const std::vector<xjson_path_type> &paths, const std::string &name,
      const nl::json &j1, const xeus::buffer_sequence &, const nl::json &j2,
      const xeus::buffer_sequence &) {
    // For a widget with no binary buffer, compare the patches
    if (paths.empty()) {
      return j1 == j2;
    } else {
      // For a property with no binary buffer, compare the patches
      if (std::find_if(paths.cbegin(), paths.cend(), [name](const auto &v) {
            return !v.empty() && v[0] == name;
          }) == paths.cend()) {
        return j1 == j2;
      } else {
        // TODO: handle the comparison of binary buffers.
        return true;
      }
    }
  }

  void xtransport_base::finalize_display(xeus::xguid const &id) {
    nl::json mime_bundle;

    // application/vnd.jupyter.widget-view+json
    nl::json widgets_json;
    widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
    widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
    widgets_json["model_id"] = id;
    mime_bundle["application/vnd.jupyter.widget-view+json"] =
        std::move(widgets_json);

    // text/plain
    mime_bundle["text/plain"] = "A Jupyter widget";

    ::xeus::get_interpreter().display_data(
        std::move(mime_bundle), nl::json::object(), nl::json::object());
  }

  void xtransport_base::finalize_send_patch(
      xeus::xcomm const &comm, nl::json &&patch,
      xeus::buffer_sequence &&buffers, nl::json &&paths) {
    // metadata
    nl::json metadata;
    metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

    // data
    nl::json data;
    data["method"] = "update";
    data["state"] = std::move(patch);
    data["buffer_paths"] = std::move(paths);

    // send
    comm.send(std::move(metadata), std::move(data), std::move(buffers));
  }

  void xtransport_base::finalize_send(xeus::xcomm const &comm,
                                      nl::json &&content,
                                      xeus::buffer_sequence &&buffers) {
    // metadata
    nl::json metadata;
    metadata["version"] = XWIDGETS_PROTOCOL_VERSION;

    // data
    nl::json data;
    data["method"] = "custom";
    data["content"] = std::move(content);

    // send
    comm.send(std::move(metadata), std::move(data), std::move(buffers));
  }

  const std::vector<xjson_path_type> &xtransport_base::finalize_buffer_paths() {
    static const std::vector<xjson_path_type> default_buffer_paths;
    return default_buffer_paths;
  }
}
