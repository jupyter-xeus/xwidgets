/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_EITHER_HPP
#define XWIDGETS_EITHER_HPP

#include <stdexcept>
#include <type_traits>
#include <unordered_set>

#include "xtl/xtype_traits.hpp"

#include "xeus/xjson.hpp"

namespace xw
{
    template <class V>
    class xeither;
}

namespace xp
{
    template <class T>
    struct xvalidation_type;

    template <class V>
    struct xvalidation_type<xw::xeither<V>>
    {
        using type = V;
    };
}

namespace xw
{

    /***********************
     * xeither declaration *
     ***********************/

    template <class V>
    xeither<V> either(std::unordered_set<V>&&);

    template <class V>
    xeither<V> either(const std::unordered_set<V>&);

    template <class V, class T>
    xeither<V> either(std::unordered_set<V>&&, T&&);

    template <class V, class T>
    xeither<V> either(const std::unordered_set<V>&, T&&);

    template <class V>
    class xeither
    {
    public:

        using value_type = V;
        using options_type = std::unordered_set<V>;

        inline xeither() {} // TODO: delete default constructor and use ADL overload of to_json / from_json

        xeither(const options_type&);
        xeither(options_type&&);
        template <class T>
        xeither(const options_type&, T&&);
        template <class T>
        xeither(options_type&&, T&&);

        value_type value() && noexcept;
        const value_type& value() const & noexcept;
        options_type options() && noexcept;
        const options_type& options() const & noexcept;
        operator value_type() const noexcept;

        template <class T>
        inline std::enable_if_t<
           xtl::conjunction<
             xtl::negation<std::is_same<xeither<V>, std::decay_t<T>>>,
             std::is_constructible<V, T>,
             std::is_assignable<std::add_lvalue_reference_t<V>, T>
           >::value,
        xeither&> operator=(T&& rhs)
        {
            if (m_options.find(rhs) == m_options.end())
            {
                throw std::runtime_error("Invalid value in xeither");
            }
            m_value = std::forward<T>(rhs);
            return *this;
        }

        template <class T>
        inline std::enable_if_t<
           xtl::conjunction<
             xtl::negation<std::is_same<xeither<V>, xeither<T>>>,
             std::is_constructible<V, std::add_lvalue_reference_t<std::add_const_t<T>>>,
             std::is_assignable<std::add_lvalue_reference_t<V>, T>
             //xtl::negation<detail::converts_from_xeither<V, T>>,
             //xtl::negation<detail::assigns_from_xeither<V, T>>
           >::value,
        xeither&> operator=(const xeither<T>&& rhs)
        {
            m_value = std::move(rhs).value();
            return *this;
        }

    private:

        options_type m_options;
        value_type m_value;
    };

    /******************
     * implementation *
     ******************/

    template <class V>
    xeither<V> either(std::unordered_set<V>&& options)
    {
        return xeither<V>(std::move(options));
    }

    template <class V>
    xeither<V> either(const std::unordered_set<V>& options)
    {
        return xeither<V>(options);
    }

    template <class V, class T>
    xeither<V> either(std::unordered_set<V>&& options, T&& value)
    {
        return xeither<V>(std::move(options), std::forward<T>(value));
    }

    template <class V, class T>
    xeither<V> either(const std::unordered_set<V>& options, T&& value)
    {
        return xeither<V>(options, std::forward<T>(value));
    }

    template <class V>
    inline void to_json(xeus::xjson&, const xeither<V>&);

    template <class V>
    void from_json(const xeus::xjson&, xeither<V>&);

    /**************************
     * xeither implementation *
     **************************/

    template <class V>
    inline xeither<V>::xeither(const options_type& options)
        : m_options(options)
    {
        if (options.empty())
        {
            throw std::runtime_error("Options cannot be an empty set");
        }
        else
        {
            m_value = *(m_options.cbegin());
        }
    }

    template <class V>
    inline xeither<V>::xeither(options_type&& options)
        : m_options(std::move(options))
    {
        if (options.empty())
        {
            throw std::runtime_error("Options cannot be an empty set");
        }
        else
        {
            m_value = *(m_options.cbegin());
        }
    }

    template <class V>
    template <class T>
    inline xeither<V>::xeither(const options_type& options, T&& value)
        : m_options(options)
    {
        if (m_options.find(value) == m_options.end())
        {
            throw std::runtime_error("Invalid value in xeither");
        }
        m_value = std::forward<T>(value);
    }

    template <class V>
    template <class T>
    inline xeither<V>::xeither(options_type&& options, T&& value)
        : m_options(std::move(options))
    {
        if (m_options.find(value) == m_options.end())
        {
            throw std::runtime_error("Invalid value in xeither");
        }
        m_value = std::forward<T>(value);
    }

    template <class V>
    inline auto xeither<V>::value() const & noexcept -> const value_type&
    {
        return m_value;
    }

    template <class V>
    inline auto xeither<V>::value() && noexcept -> value_type
    {
        return m_value;
    }

    template <class V>
    inline auto xeither<V>::options() const & noexcept -> const options_type&
    {
        return m_options;
    }

    template <class V>
    inline xeither<V>::operator value_type() const noexcept
    {
        return m_value;
    }

    template <class V>
    inline void to_json(xeus::xjson& j, const xeither<V>& o)
    {
        j = o.value();
    }

    template <class V>
    void from_json(const xeus::xjson& j, xeither<V>& o)
    {
        o = j.template get<V>();
    }
}

#endif
