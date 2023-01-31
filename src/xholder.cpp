#include "xwidgets/xholder.hpp"

#include <string>
#include <utility>

namespace xw
{
    xholder::xholder()
        : p_holder(nullptr)
    {
    }

    xholder::xholder(detail::xholder_impl* holder)
        : p_holder(holder)
    {
    }

    xholder::~xholder()
    {
        delete p_holder;
    }

    xholder::xholder(const xholder& rhs)
        : p_holder(rhs.p_holder ? rhs.p_holder->clone() : nullptr)
    {
    }

    xholder::xholder(xholder&& rhs)
        : p_holder(rhs.p_holder)
    {
        rhs.p_holder = nullptr;
    }

    xholder& xholder::operator=(const xholder& rhs)
    {
        using std::swap;
        xholder tmp(rhs);
        swap(*this, tmp);
        return *this;
    }

    xholder& xholder::operator=(xholder&& rhs)
    {
        using std::swap;
        xholder tmp(std::move(rhs));
        swap(*this, tmp);
        return *this;
    }

    void xholder::swap(xholder& rhs)
    {
        std::swap(p_holder, rhs.p_holder);
    }

    void xholder::display() const
    {
        check_holder();
        p_holder->display();
    }

    xeus::xguid xholder::id() const
    {
        check_holder();
        return p_holder->id();
    }

    void xholder::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        check_holder();
        return p_holder->serialize_state(state, buffers);
    }

    xtl::any xholder::value() &
    {
        check_holder();
        return p_holder->value();
    }

    const xtl::any xholder::value() const&
    {
        check_holder();
        return p_holder->value();
    }

    void xholder::check_holder() const
    {
        if (p_holder == nullptr)
        {
            throw std::runtime_error("The holder does not contain a widget");
        }
    }

    void swap(xholder& lhs, xholder& rhs)
    {
        lhs.swap(rhs);
    }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    void to_json(nl::json& j, const xholder& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    void from_json(const nl::json& j, xholder& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        o = make_id_holder(guid);
    }

    nl::json mime_bundle_repr(const xholder& val)
    {
        nl::json mime_bundle;

        // application/vnd.jupyter.widget-view+json
        nl::json widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = val.id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget";
        return mime_bundle;
    }
}
