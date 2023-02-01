/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_HOLDER_HPP
#define XWIDGETS_HOLDER_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <nlohmann/json.hpp>
#include <xeus/xguid.hpp>
#include <xeus/xmessage.hpp>
#include <xtl/xany.hpp>
#include <xtl/xclosure.hpp>

#include "xbinary.hpp"
#include "xwidgets_config.hpp"

namespace nl = nlohmann;

namespace xw
{
    namespace detail
    {
        class xholder_impl;
    }

    template <class D>
    class xtransport;

    /***********************
     * xholder declaration *
     ***********************/

    class XWIDGETS_API xholder
    {
    public:

        using implementation_type = detail::xholder_impl;

        xholder();
        ~xholder();
        xholder(const xholder& rhs);
        xholder(xholder&& rhs);
        template <class D>
        xholder(const xtransport<D>& rhs);
        template <class D>
        xholder(xtransport<D>&& rhs);
        template <class D, class = std::enable_if_t<std::is_base_of<xtransport<D>, D>::value, void>>
        xholder(std::shared_ptr<D> rhs);
        xholder(implementation_type* holder);

        xholder& operator=(const xholder& rhs);
        xholder& operator=(xholder&& rhs);

        template <class D>
        xholder& operator=(const xtransport<D>& rhs);
        template <class D>
        xholder& operator=(xtransport<D>&& rhs);
        template <class D>
        std::enable_if_t<std::is_base_of<xtransport<D>, D>::value, xholder&> operator=(std::shared_ptr<D> ptr);

        void swap(xholder& rhs);

        void display() const;
        xeus::xguid id() const;
        void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const;
        const std::vector<xjson_path_type>& buffer_paths() const;

        xtl::any value() &;
        const xtl::any value() const&;

        template <class D>
        D& get() &;
        template <class D>
        const D& get() const&;

    private:

        void check_holder() const;

        implementation_type* p_holder;
    };

    XWIDGETS_API void swap(xholder& lhs, xholder& rhs);

    /******************************
     * holder makers declarations *
     ******************************/

    template <class D>
    xholder make_weak_holder(xtransport<D>* ptr);

    template <class D>
    xholder make_owning_holder(xtransport<D>&& value);

    XWIDGETS_API xholder make_id_holder(xeus::xguid id);

    template <class D>
    xholder make_shared_holder(std::shared_ptr<xtransport<D>> ptr);

    /*************************************
     * to_json and from_json declaration *
     *************************************/

    XWIDGETS_API void to_json(nl::json& j, const xholder& o);

    XWIDGETS_API void from_json(const nl::json& j, xholder& o);

    /********************************
     * mime_bundle_repr declaration *
     ********************************/

    XWIDGETS_API nl::json mime_bundle_repr(const xholder& val);

    /*************************
     * holder implementation *
     *************************/

    namespace detail
    {
        class xholder_impl
        {
        public:

            xholder_impl() = default;
            virtual xholder_impl* clone() const = 0;
            virtual ~xholder_impl() = default;

            virtual void display() const = 0;
            virtual xeus::xguid id() const = 0;
            virtual void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const = 0;
            virtual const std::vector<xjson_path_type>& buffer_paths() const = 0;

            virtual xtl::any value() & = 0;
            virtual const xtl::any value() const& = 0;

        protected:

            xholder_impl(const xholder_impl&) = default;
            xholder_impl(xholder_impl&&) = default;
            xholder_impl& operator=(const xholder_impl&) = default;
            xholder_impl& operator=(xholder_impl&&) = default;
        };

        template <class D>
        class xholder_owning : public xholder_impl
        {
        public:

            using base_type = xholder_impl;

            xholder_owning(const xtransport<D>& value)
                : base_type()
                , m_value(value.derived_cast())
            {
            }

            xholder_owning(xtransport<D>&& value)
                : base_type()
                , m_value(std::move(value.derived_cast()))
            {
            }

            ~xholder_owning() override = default;

            base_type* clone() const override
            {
                return new xholder_owning(*this);
            }

            void display() const override
            {
                m_value.display();
            }

            xeus::xguid id() const override
            {
                return m_value.id();
            }

            void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const override
            {
                return m_value.serialize_state(state, buffers);
            }

            const std::vector<xjson_path_type>& buffer_paths() const override
            {
                return m_value.buffer_paths();
            }

            xtl::any value() & override
            {
                return xtl::closure(m_value);
            }

            const xtl::any value() const& override
            {
                return xtl::closure(m_value);
            }

        private:

            xholder_owning(const xholder_owning&) = default;
            xholder_owning(xholder_owning&&) = default;
            xholder_owning& operator=(const xholder_owning&) = default;
            xholder_owning& operator=(xholder_owning&&) = default;

            D m_value;
        };

        template <class D>
        class xholder_weak : public xholder_impl
        {
        public:

            using base_type = xholder_impl;

            xholder_weak(xtransport<D>* ptr)
                : base_type()
                , p_value(&(ptr->derived_cast()))
            {
            }

            ~xholder_weak() override
            {
                p_value = nullptr;
            }

            base_type* clone() const override
            {
                return new xholder_weak(*this);
            }

            void display() const override
            {
                p_value->display();
            }

            xeus::xguid id() const override
            {
                return p_value->id();
            }

            void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const override
            {
                return p_value->serialize_state(state, buffers);
            }

            const std::vector<xjson_path_type>& buffer_paths() const override
            {
                return p_value->buffer_paths();
            }

            xtl::any value() & override
            {
                return xtl::closure(*p_value);
            }

            const xtl::any value() const& override
            {
                return xtl::closure(*p_value);
            }

        private:

            xholder_weak(const xholder_weak&) = default;
            xholder_weak(xholder_weak&&) = default;
            xholder_weak& operator=(const xholder_weak&) = default;
            xholder_weak& operator=(xholder_weak&&) = default;

            D* p_value;
        };

        template <class D>
        class xholder_shared : public xholder_impl
        {
        public:

            using base_type = xholder_impl;
            using pointer = std::shared_ptr<D>;

            xholder_shared(pointer ptr)
                : base_type()
                , p_value(ptr)
            {
            }

            xholder_shared(xtransport<D>* ptr)
                : base_type()
                , p_value(&(ptr->derived_cast()))
            {
            }

            ~xholder_shared() override = default;

            base_type* clone() const override
            {
                return new xholder_shared(*this);
            }

            void display() const override
            {
                p_value->display();
            }

            xeus::xguid id() const override
            {
                return p_value->id();
            }

            void serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const override
            {
                return p_value->serialize_state(state, buffers);
            }

            const std::vector<xjson_path_type>& buffer_paths() const override
            {
                return p_value->buffer_paths();
            }

            xtl::any value() & override
            {
                return xtl::closure(*p_value);
            }

            const xtl::any value() const& override
            {
                return xtl::closure(*p_value);
            }

        private:

            pointer p_value;
        };
    }

    template <class D>
    xholder make_weak_holder(xtransport<D>* ptr)
    {
        return xholder(new detail::xholder_weak<D>(ptr));
    }

    template <class D>
    xholder make_owning_holder(xtransport<D>&& value)
    {
        return xholder(new detail::xholder_owning<D>(std::move(value)));
    }

    template <class D>
    inline xholder make_shared_holder(std::shared_ptr<xtransport<D>> ptr)
    {
        return xholder(new detail::xholder_shared<D>(std::static_pointer_cast<D>(ptr)));
    }

    /*******************************************
     * xholder template methods implementation *
     *******************************************/

    template <class D>
    xholder::xholder(const xtransport<D>& rhs)
        : xholder(make_id_holder(rhs.id()))
    {
    }

    template <class D>
    xholder::xholder(xtransport<D>&& rhs)
        : xholder(make_owning_holder(std::move(rhs)))
    {
    }

    template <class D, class>
    xholder::xholder(std::shared_ptr<D> rhs)
        : xholder(make_shared_holder<D>(rhs))
    {
    }

    template <class D>
    xholder& xholder::operator=(const xtransport<D>& rhs)
    {
        using std::swap;
        xholder tmp(make_id_holder(rhs.id()));
        swap(tmp, *this);
        return *this;
    }

    template <class D>
    xholder& xholder::operator=(xtransport<D>&& rhs)
    {
        using std::swap;
        xholder tmp(make_owning_holder(std::move(rhs)));
        swap(tmp, *this);
        return *this;
    }

    template <class D>
    std::enable_if_t<std::is_base_of<xtransport<D>, D>::value, xholder&>
    xholder::operator=(std::shared_ptr<D> ptr)
    {
        using std::swap;
        xholder tmp(make_shared_holder<D>(ptr));
        swap(tmp, *this);
        return *this;
    }

    template <class D>
    D& xholder::get() &
    {
        return xtl::any_cast<xtl::closure_wrapper<D&>>(this->value()).get();
    }

    template <class D>
    const D& xholder::get() const&
    {
        return xtl::any_cast<xtl::closure_wrapper<const D&>>(this->value()).get();
    }
}

#endif
