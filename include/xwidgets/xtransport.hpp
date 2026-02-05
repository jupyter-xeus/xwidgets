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
#include <string>
#include <utility>

#include <xeus/xcomm.hpp>
#include <xeus/xinterpreter.hpp>

#include "xcommon.hpp"
#include "xholder.hpp"
#include "xregistry.hpp"
#include "xwidgets_config.hpp"

namespace xw
{
    // Properties

    template <class P>
    inline void
    set_property_from_patch(P& property, const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            typename P::value_type value;
            xwidgets_deserialize(value, *it, buffers);
            property = value;
        }
    }

    /**************************
     * xtransport declaration *
     **************************/

    template <class D>
    class xtransport : public xcommon
    {
    public:

        using base_type = xcommon;
        using derived_type = D;

        derived_type& derived_cast() noexcept
        {
            return *static_cast<derived_type*>(this);
        }

        const derived_type& derived_cast() const noexcept
        {
            return *static_cast<const derived_type*>(this);
        }

        using base_type::notify;

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

    template <class D>
    void from_json(const nl::json& j, xtransport<D>& o);

    /*****************************
     * xtransport implementation *
     *****************************/

    template <class D>
    inline xtransport<D>::xtransport()
        : base_type()
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
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with
                                                       // `this`.
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
        get_transport_registry().register_weak(this);  // Replacing the address of the moved transport with
                                                       // `this`.
        return *this;
    }

    template <class D>
    inline void xtransport<D>::open()
    {
        // serialize state
        nl::json state;
        xeus::buffer_sequence buffers;
        this->derived_cast().serialize_state(state, buffers);

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
            // Set the current message in ``xcommom::hold()``
            // As a result ``x::commom`` will know that the change is coming from the frontend
            this->hold() = std::addressof(message);
            insert_buffer_paths(const_cast<nl::json&>(state), buffer_paths);
            // This will potentially change the properties of the widget.
            // As a result, ``xp::observed`` will call ``xcommon::notify`
            /*D*/
            this->derived_cast().apply_patch(state, buffers);
            /*D*/
            // Clear current message.
            this->hold() = nullptr;
        }
        else if (method == "request_state")
        {
            nl::json state;
            xeus::buffer_sequence buffers;
            /*D*/
            this->derived_cast().serialize_state(state, buffers);
            /*D*/
            send_patch(std::move(state), std::move(buffers));
        }
        else if (method == "custom")
        {
            auto it = data.find("content");
            if (it != data.end())
            {
                /*D*/
                this->derived_cast().handle_custom_message(it.value());
                /*D*/
            }
        }
    }

    /****************************
     * from_json implementation *
     ****************************/

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
