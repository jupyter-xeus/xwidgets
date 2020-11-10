/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_MATERIALIZE_HPP
#define XWIDGETS_MATERIALIZE_HPP

#include <utility>

#include "nlohmann/json.hpp"

#include "xwidgets_config.hpp"
#include "xcommon.hpp"

namespace nl = nlohmann;

namespace xw
{
    /****************************
     * xmaterialize declaration *
     ****************************/

    template <template <class> class B, class... P>
    class xmaterialize final : public B<xmaterialize<B, P...>>
    {
    public:

        using self_type = xmaterialize<B, P...>;
        using base_type = B<self_type>;

        template <class... A>
        xmaterialize(A&&...);

        template <class... A>
        static xmaterialize initialize(A&&...);

        ~xmaterialize();

        xmaterialize(const xmaterialize&);
        xmaterialize& operator=(const xmaterialize&);

        xmaterialize(xmaterialize&&);
        xmaterialize& operator=(xmaterialize&&);

        xmaterialize<B, P...> finalize() &&;

    private:

        template <class... A>
        xmaterialize(bool open, A&&...);

        bool m_generator;
    };

    /*******************************
     * xmaterialize implementation *
     *******************************/

    template <template <class> class B, class... P>
    template <class... A>
    inline xmaterialize<B, P...>::xmaterialize(A&&... args)
        : xmaterialize(false, std::forward<A>(args)...)
    {
    }

    // private constructor determining whether the comm should be open
    template <template <class> class B, class... P>
    template <class... A>
    inline xmaterialize<B, P...>::xmaterialize(bool generator, A&&... args)
        : base_type(std::forward<A>(args)...), m_generator(generator)
    {
        if (!m_generator)
        {
            this->open();
        }
    }

    template <template <class> class B, class... P>
    template <class... A>
    inline auto xmaterialize<B, P...>::initialize(A&&... args) -> xmaterialize
    {
        return xmaterialize(true, std::forward<A>(args)...);
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>::~xmaterialize()
    {
        if (!m_generator && !this->moved_from())
        {
            this->close();
        }
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>::xmaterialize(const xmaterialize& rhs)
        : base_type(rhs)
    {
        this->open();
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>& xmaterialize<B, P...>::operator=(const xmaterialize& rhs)
    {
        if (!m_generator)
        {
            this->close();
        }
        base_type::operator=(rhs);
        this->open();
        return *this;
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>::xmaterialize(xmaterialize&&) = default;

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>& xmaterialize<B, P...>::operator=(xmaterialize&& rhs) = default;

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...> xmaterialize<B, P...>::finalize() &&
    {
        return *this;
    }

    /**********************************************************
     * Specialization of mime_bundle_repr for Jupyter Widgets *
     **********************************************************/

    template <template <class> class B, class... P>
    nl::json mime_bundle_repr(const xmaterialize<B, P...>& val)
    {
        return mime_bundle_repr(static_cast<const xcommon&>(val));
    }

    /*************
     * Generator *
     *************/  

    template <template <class> class B, class... P, class... A>
    inline xmaterialize<B, P...> generator(A&&... args)
    {
        return xmaterialize<B, P...>::initialize(std::forward<A>(args)...);
    }
}

#endif
