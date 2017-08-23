#ifndef XWIDGETS_HOLDER_HPP
#define XWIDGETS_HOLDER_HPP

#include <utility>

#include "xeus/xguid.hpp"
#include "xeus/xjson.hpp"

namespace xw
{
    template <class D>
    class xtransport;

    namespace detail
    {
        template <template <class> class CRTP>
        class xholder_impl;
    }

    /***********************
     * xholder declaration *
     ***********************/

    template <template <class> class CRTP = xtransport>
    class xholder
    {
    public:

        xholder();
        ~xholder();
        xholder(const xholder& rhs);
        xholder(xholder&& rhs);
        xholder(detail::xholder_impl<CRTP>* holder);

        xholder& operator=(const xholder& rhs);
        xholder& operator=(xholder&& rhs);

        template <class D>
        xholder& operator=(const CRTP<D>& rhs);

        template <class D>
        xholder& operator=(CRTP<D>&& rhs);

        void swap(xholder& rhs);

        void display() const;
        xeus::xguid id() const;

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

        detail::xholder_impl<CRTP>* p_holder;
    };

    template <template <class> class CRTP>
    inline void swap(xholder<CRTP>& lhs, xholder<CRTP>& rhs)
    {
        lhs.swap(rhs);
    }

    /*************************************
     * to_json and from_json declaration *
     *************************************/

    template <template <class> class CRTP>
    void to_json(xeus::xjson& j, const xholder<CRTP>& o);
    template <template <class> class CRTP>
    void from_json(const xeus::xjson& j, xholder<CRTP>& o);

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
                  m_value(std::move(value).derived_cast())
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
        
            inline D& value() & noexcept { return m_value; }
            inline const D& value() const & noexcept { return m_value; }
            inline D value() && noexcept { return m_value; } 

        private:

            xholder_owning(const xholder_owning&) = default;
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
        
            inline D& value() & noexcept { return *p_value; }
            inline const D& value() const & noexcept { return *p_value; }
            inline D value() && noexcept { return *p_value; } 

        private:

            xholder_weak(const xholder_weak&) = default;
            D* p_value;
        };
    }

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_weak_holder(CRTP<D>* ptr)
    {
        return xholder<CRTP>(new detail::xholder_weak<CRTP, D>(ptr));
    }

    template <template <class> class CRTP, class D>
    xholder<CRTP> make_owning_holder(const CRTP<D>& value)
    {
        return xholder<CRTP>(new detail::xholder_owning<CRTP, D>(value));
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
    xholder<CRTP>::xholder() : p_holder(nullptr)
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(detail::xholder_impl<CRTP>* holder) : p_holder(holder)
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::~xholder()
    {
        delete p_holder;
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(const xholder& rhs) : p_holder(rhs.p_holder->clone())
    {
    }

    template <template <class> class CRTP>
    xholder<CRTP>::xholder(xholder&& rhs) : p_holder(rhs.p_holder)
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
        if (p_holder != nullptr)
        {
            p_holder->display();
        }
    }

    template <template <class> class CRTP>
    xeus::xguid xholder<CRTP>::id() const
    {
        if (p_holder != nullptr)
        {
            return p_holder->id();
        }
        else
        {
            // TODO: throw?
            return xeus::xguid();
        }
    }

    template <template <class> class CRTP>
    template <class D, bool owning>
    D& xholder<CRTP>::get() &
    {
        if (owning)
        {
            return dynamic_cast<detail::xholder_owning<CRTP, D>*>(p_holder)->value();
        }
        else
        {
            return dynamic_cast<detail::xholder_weak<CRTP, D>*>(p_holder)->value();
        }
    }

    template <template <class> class CRTP>
    template <class D, bool owning>
    const D& xholder<CRTP>::get() const &
    {
        if (owning)
        {
            return dynamic_cast<detail::xholder_owning<CRTP, D>*>(p_holder)->value();
        }
        else
        {
            return dynamic_cast<detail::xholder_weak<CRTP, D>*>(p_holder)->value();
        }
    }

    /*
    template <template <class> class CRTP>
    template <class D, bool owning, typename T = std::enable_if_t<owning>>
    D xholder<CRTP>::get() &&
    {
         return dynamic_cast<detail::xholder_owning<CRTP, D>*>(p_holder)->value();
    }

    template <template <class> class CRTP>
    template <class D, bool owning, typename T = std::enable_if_t<!owning>>
    D& xholder<CRT>::get() &&
    {
         return dynamic_cast<detail::xholder_weak<CRTP, D>*>(p_holder)->value();
    }
    */

    /****************************************
     * to_json and from_json implementation *
     ****************************************/

    template <template <class> class CRTP>
    inline void to_json(xeus::xjson& j, const xholder<CRTP>& o)
    {
        j = "IPY_MODEL_" + guid_to_hex(o.id());
    }

    template <template <class> class CRTP>
    inline void from_json(const xeus::xjson& j, xholder<CRTP>& o)
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

