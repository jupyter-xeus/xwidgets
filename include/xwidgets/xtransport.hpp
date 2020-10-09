/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TRANSPORT_HPP
#define XWIDGETS_TRANSPORT_HPP

#include <functional>
#include <list>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "xeus/xcomm.hpp"
#include "xeus/xinterpreter.hpp"

#include "xbinary.hpp"
#include "xfactory.hpp"
#include "xholder.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
    /**********************************
     * Comm target handling functions *
     **********************************/

    inline const char* get_widget_target_name()
    {
        return "jupyter.widget";
    }

    inline void xobject_comm_opened(xeus::xcomm&& comm, const xeus::xmessage& msg)
    {
        const nl::json& content = msg.content();
        const nl::json& metadata = msg.metadata();

        std::string version;
        try
        {
            version = metadata.at("version").get<std::string>();
        }
        catch (std::out_of_range)
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

    inline int register_widget_target()
    {
        xeus::get_interpreter()
            .comm_manager()
            .register_comm_target(get_widget_target_name(), xobject_comm_opened);
        return 0;
    }

    inline xeus::xtarget* get_widget_target()
    {
        static int registered = register_widget_target();
        return ::xeus::get_interpreter()
            .comm_manager()
            .target(get_widget_target_name());
    }

    /**********************************************
     * property serialization and deserialization *
     **********************************************/

    // Values

    template <class T>
    inline void xwidgets_serialize(const T& value, nl::json& j, xeus::buffer_sequence&)
    {
        j = value;
    }

    template <class T>
    inline void xwidgets_deserialize(T& value, const nl::json& j, const xeus::buffer_sequence&)
    {
        value = j.template get<T>();
    }

    // Properties

    template <class P>
    inline void set_property_from_patch(P& property, const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            typename P::value_type value;
            xwidgets_deserialize(value, *it, buffers);
            property = value;
        }
    }

    /***********************
     * xcommon declaration *
     ***********************/

    class XWIDGETS_API xcommon
    {
    public:

        xeus::xguid id() const noexcept;
        void display() const;

    protected:

        xcommon();
        xcommon(xeus::xcomm&&);
        ~xcommon();
        xcommon(const xcommon&);
        xcommon(xcommon&&);
        xcommon& operator=(const xcommon&);
        xcommon& operator=(xcommon&&);

        bool moved_from() const noexcept;
        void handle_custom_message(const nl::json&);
        xeus::xcomm& comm();
        const xeus::xcomm& comm() const;
        const xeus::xmessage*& hold();
        const xeus::xmessage* const& hold() const;
        const std::vector<xjson_path_type>& buffer_paths() const;

        void open(nl::json&& patch, xeus::buffer_sequence&& buffers);
        void close();

        template <class T>
        void notify(const std::string& name, const T& value) const;
        void send(nl::json&&, xeus::buffer_sequence&&) const;
        void send_patch(nl::json&&, xeus::buffer_sequence&&) const;

    private:

        bool same_patch(const std::string&,
                        const nl::json&,
                        const xeus::buffer_sequence&,
                        const nl::json&,
                        const xeus::buffer_sequence&) const;

        bool m_moved_from;
        const xeus::xmessage* m_hold;
        xeus::xcomm m_comm;
        std::vector<xjson_path_type> m_buffer_paths;
    };

    /**************************
     * xtransport declaration *
     **************************/

    template <class D>
    class xtransport : public xcommon
    {
    public:

        using base_type = xcommon;
        using derived_type = D;

        derived_type& derived_cast() & noexcept;
        const derived_type& derived_cast() const & noexcept;
        derived_type derived_cast() && noexcept;

    protected:

        xtransport();
        xtransport(xeus::xcomm&&, bool owning = false);
        ~xtransport();
        xtransport(const xtransport&);
        xtransport(xtransport&&);
        xtransport& operator=(const xtransport&);
        xtransport& operator=(xtransport&&);

        void open();
        void close();

    private:

        void handle_message(const xeus::xmessage&);
    };

    template <class T, class R = void>
    struct enable_xtransport
    {
        using type = std::enable_if_t<std::is_base_of<xtransport<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xtransport_t = typename enable_xtransport<T, R>::type;

    /****************************************
     * to_json and from_json specialization *
     ****************************************/

    void to_json(nl::json& j, const xcommon& o);

    template <class D>
    void from_json(const nl::json& j, xtransport<D>& o);

    /**************************
     * xcommon implementation *
     **************************/

    inline xcommon::xcommon()
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(get_widget_target(), xeus::new_xguid())
    {
    }

    inline xcommon::~xcommon()
    {
    }

    inline xcommon::xcommon(xeus::xcomm&& comm)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(std::move(comm))
    {
    }

    inline xcommon::xcommon(const xcommon& other)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(other.m_comm)
    {
    }

    inline xcommon::xcommon(xcommon&& other)
        : m_moved_from(false),
          m_hold(nullptr),
          m_comm(std::move(other.m_comm))
    {
        other.m_moved_from = true;
    }

    inline xcommon& xcommon::operator=(const xcommon& other)
    {
        m_moved_from = false;
        m_hold = nullptr;
        m_comm = other.m_comm;
        return *this;
    }

    inline xcommon& xcommon::operator=(xcommon&& other)
    {
        other.m_moved_from = true;
        m_moved_from = false;
        m_hold = nullptr;
        m_comm = std::move(other.m_comm);
        return *this;
    }

    inline auto xcommon::id() const noexcept -> xeus::xguid
    {
        return m_comm.id();
    }

    inline void xcommon::display() const
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

        ::xeus::get_interpreter().display_data(
            std::move(mime_bundle),
            nl::json::object(),
            nl::json::object());
    }

    inline void xcommon::send(nl::json&& content, xeus::buffer_sequence&& buffers) const
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

    inline void xcommon::handle_custom_message(const nl::json& /*content*/)
    {
    }
    
    inline xeus::xcomm& xcommon::comm()
    {
        return m_comm;
    }

    inline const xeus::xcomm& xcommon::comm() const
    {
        return m_comm;
    }

    inline const xeus::xmessage*& xcommon::hold()
    {
        return m_hold;
    }

    inline const xeus::xmessage* const& xcommon::hold() const
    {
        return m_hold;
    }

    inline bool xcommon::moved_from() const noexcept
    {
        return m_moved_from;
    }

    inline const std::vector<xjson_path_type>& xcommon::buffer_paths() const
    {
        return m_buffer_paths;
    }

    inline void xcommon::send_patch(nl::json&& patch, xeus::buffer_sequence&& buffers) const
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

    inline void xcommon::open(nl::json&& patch, xeus::buffer_sequence&& buffers)
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

    inline void xcommon::close()
    {
        // close
        m_comm.close(nl::json::object(), nl::json::object(), xeus::buffer_sequence());
    } 

    inline bool xcommon::same_patch(const std::string& name,
                                    const nl::json& j1,
                                    const xeus::buffer_sequence&,
                                    const nl::json& j2,
                                    const xeus::buffer_sequence&) const
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
            if (std::find_if(paths.cbegin(), paths.cend(), [name](const auto& v) {
                return !v.empty() && v[0] == name;
            }) == paths.cend())
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

    template <class T>
    inline void xcommon::notify(const std::string& name, const T& value) const
    {
        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(value, state[name], buffers);

        if (m_hold != nullptr)
        {
            const auto& hold_state = m_hold->content()["data"]["state"];
            const auto& hold_buffers = m_hold->buffers();

            auto it = hold_state.find(name);
            if (it != hold_state.end())
            {
                if(same_patch(name,
                              *it,
                              hold_buffers,
                              state[name],
                              buffers))
                {
                    return;
                }
            }
        }

        send_patch(std::move(state), std::move(buffers));
    }

    /*****************************
     * xtransport implementation *
     *****************************/

    template <class D>
    inline xtransport<D>::xtransport()
        : xcommon()
    {
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
    }

    template <class D>
    inline xtransport<D>::~xtransport()
    {
        if (!this->moved_from())
        {
            get_transport_registry().unregister(this->id());
        }
    }

    template <class D>
    inline xtransport<D>::xtransport(xeus::xcomm&& comm, bool owning)
        : xcommon(std::move(comm))
    {
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        if (!owning)
        {
            get_transport_registry().register_weak(this);
        }
    }

    template <class D>
    inline xtransport<D>::xtransport(const xtransport& other)
        : xcommon(other)
    {
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
    }

    template <class D>
    inline xtransport<D>::xtransport(xtransport&& other)
        : xcommon(std::move(other))
    {
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with `this`.
    }

    template <class D>
    inline xtransport<D>& xtransport<D>::operator=(const xtransport& other)
    {
        base_type::operator=(other);
        get_transport_registry().unregister(this->id());
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);
        return *this;
    }

    template <class D>
    inline xtransport<D>& xtransport<D>::operator=(xtransport&& other)
    {
        base_type::operator=(std::move(other));
        get_transport_registry().unregister(this->id());
        this->comm().on_message(std::bind(&xtransport::handle_message, this, std::placeholders::_1));
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with `this`.
        return *this;
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() & noexcept -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() const & noexcept -> const derived_type&
    {
        return *static_cast<const derived_type*>(this);
    }

    template <class D>
    inline auto xtransport<D>::derived_cast() && noexcept -> derived_type
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline void xtransport<D>::open()
    {
        // serialize state
        nl::json state;
        xeus::buffer_sequence buffers;
        derived_cast().serialize_state(state, buffers);

        // open comm
        base_type::open(std::move(state), std::move(buffers));        
    }

    template <class D>
    inline void xtransport<D>::close()
    {
        base_type::close();
    }

    template <class D>
    inline void xtransport<D>::handle_message(const xeus::xmessage& message)
    {
        const nl::json& content = message.content();
        const nl::json& data = content["data"];
        const std::string method = data["method"];

        if (method == "update")
        {
            const nl::json& state = data["state"];
            const auto& buffers = message.buffers();
            const nl::json& buffer_paths = data["buffer_paths"];
            this->hold() = std::addressof(message);;
            insert_buffer_paths(const_cast<nl::json&>(state), buffer_paths);
            /*D*/
            derived_cast().apply_patch(state, buffers);
            /*D*/
            this->hold() = nullptr;
        }
        else if (method == "request_state")
        {
            nl::json state;
            xeus::buffer_sequence buffers;
            /*D*/
            derived_cast().serialize_state(state, buffers);
            /*D*/
            send_patch(std::move(state), std::move(buffers));
        }
        else if (method == "custom")
        {
            auto it = data.find("content");
            if (it != data.end())
            {
                /*D*/
                derived_cast().handle_custom_message(it.value());
                /*D*/
            }
        }
    }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    inline void to_json(nl::json& j, const xcommon& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    template <class D>
    inline void from_json(const nl::json& j, xtransport<D>& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        auto& holder = get_transport_registry().find(guid);
        /*D*/
        o.derived_cast() = std::move(holder.template get<D>());
        /*D*/
    }
}

#endif
