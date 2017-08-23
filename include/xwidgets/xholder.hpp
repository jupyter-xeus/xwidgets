#ifndef XWIDGETS_HOLDER_HPP
#define XWIDGETS_HOLDER_HPP

#include <utility>

#include "xeus/xguid.hpp"
#include "xeus/xjson.hpp"

namespace xeus
{
    template <class D>
    class xtransport;

    namespace detail
    {
        class xholder_impl;
    }

    /***********************
     * xholder declaration *
     ***********************/

    class xholder
    {
    public:

        xholder();
        ~xholder();
        xholder(const xholder& rhs);
        xholder(xholder&& rhs);
        xholder(detail::xholder_impl* holder);

        xholder& operator=(const xholder& rhs);
        xholder& operator=(xholder&& rhs);

        template <class D>
        xholder& operator=(const xtransport<D>& rhs);

        template <class D>
        xholder& operator=(xtransport<D>&& rhs);

        void swap(xholder& rhs);

        void display() const;
        xguid id() const;

        template <class D, bool owning>
        D& get() &;
        template <class D, bool owning>
        const D& get() const &;

        /*
        template <class D, bool owning, typename T = std::enable_if_t<owning>>
        D get() &&;
        template <class D, bool owning, typename T = std::enable_if_t<!owning>>
        D& get() &&;
        */

    private:

        detail::xholder_impl* p_holder;
    };

    inline void swap(xholder& lhs, xholder& rhs)
    {
        lhs.swap(rhs);
    }

    /*************************************
     * to_json and from_json declaration *
     *************************************/

    void to_json(xjson& j, const xholder& o);
    void from_json(const xjson& j, xholder& o);

    namespace detail
    {
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
            virtual xguid id() const = 0;

        protected:

            xholder_impl(const xholder_impl&) = default;
        };
     
        template <class D>
        class xholder_owning : public xholder_impl
        {
        public:
        
            using base_type = xholder_impl;
        
            xholder_owning(const xtransport<D>& value)
                : base_type(),
                  m_value(value.derived_cast())
            {
            }
        
            xholder_owning(xtransport<D>&& value)
                : base_type(),
                  m_value(std::move(value).derived_cast())
            {
            }
        
            virtual ~xholder_owning()
            {
            }
        
            virtual xholder_impl* clone() const override
            {
                return new xholder_owning(*this);
            }

            virtual void display() const override
            {
                m_value.display();
            }
        
            virtual xguid id() const override
            {
                return m_value.id();
            }
        
            inline D& value() & noexcept { return m_value; }
            inline const D& value() const & noexcept { return m_value; }
            inline D value() && noexcept { return m_value; } 

        private:

            xholder_owning(const xholder_owning&) = default;
            D m_value;
        };

        template <class D>
        class xholder_weak : public xholder_impl
        {
        public:

            using base_type = xholder_impl;

            xholder_weak(xtransport<D>* ptr)
                : base_type(),
                  p_value(&(ptr->derived_cast()))
            {
            }
        
            virtual ~xholder_weak()
            {
                p_value = nullptr;
            }

            virtual xholder_impl* clone() const override
            {
                return new xholder_weak(*this);
            }

            virtual void display() const override
            {
                p_value->display();
            }
        
            virtual xguid id() const override
            {
                return p_value->id();
            }
        
            inline D& value() & noexcept { return *p_value; }
            inline const D& value() const & noexcept { return *p_value; }
            inline D value() && noexcept { return *p_value; } 

        private:

            xholder_weak(const xholder_weak&) = default;
            D* p_value;
        };
    }

    template <class D>
    xholder make_weak_holder(xtransport<D>* ptr)
    {
        return xholder(new detail::xholder_weak<D>(ptr));
    }

    template <class D>
    xholder make_owning_holder(const xtransport<D>& value)
    {
        return xholder(new detail::xholder_owning<D>(value));
    }

    template <class D>
    xholder make_owning_holder(xtransport<D>&& value)
    {
        return xholder(new detail::xholder_owning<D>(std::move(value)));
    }

    /**************************
     * xholder implementation *
     **************************/

    xholder::xholder() : p_holder(nullptr)
    {
    }

    xholder::xholder(detail::xholder_impl* holder) : p_holder(holder)
    {
    }

    xholder::~xholder()
    {
        delete p_holder;
    }

    xholder::xholder(const xholder& rhs) : p_holder(rhs.p_holder->clone())
    {
    }

    xholder::xholder(xholder&& rhs) : p_holder(rhs.p_holder)
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

    template <class D>
    xholder& xholder::operator=(xtransport<D>&& rhs)
    {
        using std::swap;
        xholder tmp(make_owning_holder(std::move(rhs)));
        swap(tmp, *this);
        return *this;
    }

    void xholder::swap(xholder& rhs)
    {
        std::swap(p_holder, rhs.p_holder);
    }

    void xholder::display() const
    {
        if (p_holder != nullptr)
        {
            p_holder->display();
        }
    }

    xguid xholder::id() const
    {
        if (p_holder != nullptr)
        {
            return p_holder->id();
        }
        else
        {
            // TODO: throw?
            return xguid();
        }
    }

    template <class D, bool owning>
    D& xholder::get() &
    {
        if (owning)
        {
            return dynamic_cast<detail::xholder_owning<D>*>(p_holder)->value();
        }
        else
        {
            return dynamic_cast<detail::xholder_weak<D>*>(p_holder)->value();
        }
    }

    template <class D, bool owning>
    const D& xholder::get() const &
    {
        if (owning)
        {
            return dynamic_cast<detail::xholder_owning<D>*>(p_holder)->value();
        }
        else
        {
            return dynamic_cast<detail::xholder_weak<D>*>(p_holder)->value();
        }
    }

    /*
    template <class D, bool owning, typename T = std::enable_if_t<owning>>
    D xholder::get() &&
    {
         return dynamic_cast<detail::xholder_owning<D>*>(p_holder)->value();
    }

    template <class D, bool owning, typename T = std::enable_if_t<!owning>>
    D& xholder::get() &&
    {
         return dynamic_cast<detail::xholder_weak<D>*>(p_holder)->value();
    }
    */

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    inline void to_json(xjson& j, const xholder& o)
    {
        j = "IPY_MODEL_" + guid_to_hex(o.id());
    }

    inline void from_json(const xjson& j, xholder& o)
    {
        /*
        std::string prefixed_guid = j;
        xguid guid = hex_to_guid(prefixed_guid.substr(10).c_str());
        auto& holder = get_transport_registry().find(guid);
        o;  // TODO: move?
        */
    }
}
#endif

