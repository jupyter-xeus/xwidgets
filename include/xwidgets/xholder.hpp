#ifndef XWIDGETS_HOLDER_HPP
#define XWIDGETS_HOLDER_HPP

#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "xtl/xany.hpp"
#include "xtl/xclosure.hpp"

#include "xeus/xguid.hpp"
#include "xeus/xjson.hpp"

namespace xw
{
    namespace detail
    {
        template <template <class> class CRTP>
        class xholder_impl;
    }

    /***********************
     * xholder declaration *
     ***********************/

    template <template <class> class CRTP>
    class xholder
    {
    public:

        using implementation_type = detail::xholder_impl<CRTP>;

        xholder();
        ~xholder();
        xholder(const xholder& rhs);
        xholder(xholder&& rhs);
        template <class D>
        xholder(const CRTP<D>& rhs);
        template <class D>
        xholder(CRTP<D>&& rhs);
        xholder(implementation_type* holder);

        xholder& operator=(const xholder& rhs);
        xholder& operator=(xholder&& rhs);

        template <class D>
        xholder& operator=(const CRTP<D>& rhs);
        template <class D>
        xholder& operator=(CRTP<D>&& rhs);

        void swap(xholder& rhs);

        void display() const;
        xeus::xguid id() const;

        xtl::any value() &;
        const xtl::any value() const &;

        template <class D>
        D& get() &;
        template <class D>
        const D& get() const &;

    private:

        void check_holder() const;

        implementation_type* p_holder;
    };

    template <template <class> class CRTP>
    inline void swap(xholder<CRTP>& lhs, xholder<CRTP>& rhs);

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_weak_holder(CRTP<D>* ptr);

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_owning_holder(CRTP<D>&& value);

    template <template <class> class CRTP>
    xholder<CRTP> make_id_holder(xeus::xguid id);

    /*************************************
     * to_json and from_json declaration *
     *************************************/

    template <template <class> class CRTP>
    void to_json(xeus::xjson& j, const xholder<CRTP>& o);

    template <template <class> class CRTP>
    void from_json(const xeus::xjson& j, xholder<CRTP>& o);

    /*************************
     * xregistry declaration *
     *************************/

    template <class D>
    class xtransport;

    class xregistry
    {
    public:

        using holder_type = xholder<xtransport>;
        using storage_type = std::unordered_map<xeus::xguid, holder_type>;

        template <class D>
        void register_weak(xtransport<D>* ptr);

        template <class D>
        void register_owning(xtransport<D>&& model);

        void unregister(xeus::xguid id);

        typename storage_type::mapped_type& find(xeus::xguid id);

    private:

        storage_type m_storage;
    };

    inline xregistry& get_transport_registry()
    {
        static xregistry instance;
        return instance;
    }

    /**************************
     * holder implementations *
     **************************/

    namespace detail
    {
        template <template <class> class CRTP>
        class xholder_impl
        {
        public:
      
            xholder_impl() = default;
            xholder_impl(xholder_impl&&) = delete;
            xholder_impl& operator=(const xholder_impl&) = delete;
            xholder_impl& operator=(xholder_impl&&) = delete;
            virtual xholder_impl* clone() const = 0;
            virtual ~xholder_impl() = default;

            virtual void display() const = 0;
            virtual xeus::xguid id() const = 0;

            virtual xtl::any value() & = 0;
            virtual const xtl::any value() const & = 0;
        
        protected:

            xholder_impl(const xholder_impl&) = default;
        };

        template <template <class> class CRTP, class D>
        class xholder_owning : public xholder_impl<CRTP>
        {
        public:
        
            using base_type = xholder_impl<CRTP>;

            xholder_owning(const CRTP<D>& value)
                : base_type(),
                  m_value(value.derived_cast())
            {
            }

            xholder_owning(CRTP<D>&& value)
                : base_type(),
                  m_value(std::move(value.derived_cast()))
            {
            }

            virtual ~xholder_owning()
            {
            }

            virtual base_type* clone() const override
            {
                return new xholder_owning(*this);
            }

            virtual void display() const override
            {
                m_value.display();
            }

            virtual xeus::xguid id() const override
            {
                return m_value.id();
            }

            virtual xtl::any value() & override
            {
                return xtl::closure(m_value);
            }

            virtual const xtl::any value() const & override
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

        template <template <class> class CRTP, class D>
        class xholder_weak : public xholder_impl<CRTP>
        {
        public:

            using base_type = xholder_impl<CRTP>;

            xholder_weak(CRTP<D>* ptr)
                : base_type(),
                  p_value(&(ptr->derived_cast()))
            {
            }

            virtual ~xholder_weak()
            {
                p_value = nullptr;
            }

            virtual base_type* clone() const override
            {
                return new xholder_weak(*this);
            }

            virtual void display() const override
            {
                p_value->display();
            }

            virtual xeus::xguid id() const override
            {
                return p_value->id();
            }

            virtual xtl::any value() & override
            {
                return xtl::closure(*p_value);
            }

            virtual const xtl::any value() const & override
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
    }

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_weak_holder(CRTP<D>* ptr)
    {
        return xholder<CRTP>(new detail::xholder_weak<CRTP, D>(ptr));
    }

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_owning_holder(CRTP<D>&& value)
    {
        return xholder<CRTP>(new detail::xholder_owning<CRTP, D>(std::move(value)));
    }

    /**************************
     * xholder implementation *
     **************************/

    template <template <class> class CRTP>
    xholder<CRTP>::xholder()
        : p_holder(nullptr)
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(detail::xholder_impl<CRTP>* holder)
        : p_holder(holder)
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::~xholder()
    {
        delete p_holder;
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(const xholder& rhs)
        : p_holder(rhs.p_holder ? rhs.p_holder->clone() : nullptr)
    {
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>::xholder(const CRTP<D>& rhs)
        : xholder(make_id_holder<CRTP>(rhs.id()))
    {
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>::xholder(CRTP<D>&& rhs)
        : xholder(make_owning_holder(std::move(rhs)))
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(xholder&& rhs)
        : p_holder(rhs.p_holder)
    {
        rhs.p_holder = nullptr;
    }

    template <template <class> class CRTP>
    xholder<CRTP>& xholder<CRTP>::operator=(const xholder& rhs)
    {
        using std::swap;
        xholder tmp(rhs);
        swap(*this, tmp);
        return *this;
    }

    template <template <class> class CRTP>
    xholder<CRTP>& xholder<CRTP>::operator=(xholder&& rhs)
    {
        using std::swap;
        xholder tmp(std::move(rhs));
        swap(*this, tmp);
        return *this;
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>& xholder<CRTP>::operator=(const CRTP<D>& rhs)
    {
        using std::swap;
        xholder<CRTP> tmp(make_id_holder<CRTP>(rhs.id()));
        swap(tmp, *this);
        return *this;
    }

    template <template <class> class CRTP>
    template <class D>
    xholder<CRTP>& xholder<CRTP>::operator=(CRTP<D>&& rhs)
    {
        using std::swap;
        xholder<CRTP> tmp(make_owning_holder(std::move(rhs)));
        swap(tmp, *this);
        return *this;
    }

    template <template <class> class CRTP>
    void xholder<CRTP>::swap(xholder& rhs)
    {
        std::swap(p_holder, rhs.p_holder);
    }

    template <template <class> class CRTP>
    void xholder<CRTP>::display() const
    {
        check_holder();
        p_holder->display();
    }

    template <template <class> class CRTP>
    xeus::xguid xholder<CRTP>::id() const
    {
        check_holder();
        return p_holder->id();
    }

    template <template <class> class CRTP>
    xtl::any xholder<CRTP>::value() &
    {
        check_holder();
        return p_holder->value();
    }

    template <template <class> class CRTP>
    const xtl::any xholder<CRTP>::value() const &
    {
        check_holder();
        return p_holder->value();
    }

    template <template <class> class CRTP>
    template <class D>
    D& xholder<CRTP>::get() &
    {
        return xtl::any_cast<xtl::closure_wrapper<D&>>(this->value()).get();
    }

    template <template <class> class CRTP>
    template <class D>
    const D& xholder<CRTP>::get() const &
    {
        return xtl::any_cast<xtl::closure_wrapper<const D&>>(this->value()).get();
    }

    template <template <class> class CRTP>
    void xholder<CRTP>::check_holder() const
    {
        if (p_holder == nullptr)
        {
            throw std::runtime_error("The holder does not contain a widget");
        }
    }

    template <template <class> class CRTP>
    inline void swap(xholder<CRTP>& lhs, xholder<CRTP>& rhs)
    {
        lhs.swap(rhs);
    }

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    template <template <class> class CRTP>
    inline void to_json(xeus::xjson& j, const xholder<CRTP>& o)
    {
        j = "IPY_MODEL_" + std::string(o.id());
    }

    template <template <class> class CRTP>
    void from_json(const xeus::xjson& j, xholder<CRTP>& o)
    {
        std::string prefixed_guid = j;
        xeus::xguid guid = prefixed_guid.substr(10).c_str();
        o = make_id_holder<CRTP>(guid);
    }

    /****************************
     * xregistry implementation *
     ****************************/

    template <class D>
    void xregistry::register_weak(xtransport<D>* ptr)
    {
        m_storage[ptr->id()] = make_weak_holder(ptr);
    }

    template <class D>
    void xregistry::register_owning(xtransport<D>&& model)
    {
        return m_storage[model.id()] = make_owning_holder(std::move(model));
    }

    inline void xregistry::unregister(xeus::xguid id)
    {
        m_storage.erase(id);
    }

    inline auto xregistry::find(xeus::xguid id) -> typename storage_type::mapped_type&
    {
        auto it = m_storage.find(id);
        if (it == m_storage.end())
        {
            throw std::runtime_error("Could not find specified id in transport registry");
        }
        return it->second;
    }

    /*******************
     * xmaker template *
     *******************/

    template <template <class> class CRTP, class... P>
    void xmaker(xeus::xcomm&& comm, const xeus::xjson& state)
    {
        auto model = xgenerator<CRTP, P...>(std::move(comm), true);
        model.apply_patch(state);
        get_transport_registry().register_owning(reinterpret_cast<xmaterialize<CRTP, P...>&&>(model));
    }

    namespace detail
    {
        template <template <class> class CRTP>
        class xholder_id : public xholder_impl<CRTP>
        {
        public:

            using base_type = xholder_impl<CRTP>;

            xholder_id(xeus::xguid id)
                : base_type(),
                  m_id(id)
            {
            }

            virtual ~xholder_id() = default;

            virtual base_type* clone() const override
            {
                return new xholder_id(*this);
            }

            virtual void display() const override
            {
                auto& holder = get_transport_registry().find(m_id);
                holder.display();
            }

            virtual xeus::xguid id() const override
            {
                auto& holder = get_transport_registry().find(m_id);
                return holder.id();
            }

            virtual xtl::any value() & override
            {
                auto& holder = get_transport_registry().find(m_id);
                return holder.value();
            }

            virtual const xtl::any value() const & override
            {
                const auto& holder = get_transport_registry().find(m_id);
                return holder.value();
            }

        private:

            xholder_id(const xholder_id&) = default;
            xholder_id(xholder_id&&) = default;
            xeus::xguid m_id;
        };
    }

    template <template <class> class CRTP>
    xholder<CRTP> make_id_holder(xeus::xguid id)
    {
        return xholder<CRTP>(new detail::xholder_id<CRTP>(id));
    }
}
#endif
