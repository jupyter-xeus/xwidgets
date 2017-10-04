/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_MATERIALIZE_HPP
#define XWIDGETS_MATERIALIZE_HPP

namespace xw
{

    template <class T, class... Args>
    T make_widget(Args&&... args)
    {
        typename T::base_type tmp(std::forward<Args>(args)...);
        return std::move(tmp.derived_cast());
    }

    /****************************
     * xmaterialize declaration *
     ****************************/

    // CRTP and mixin

    template <template <class> class B, class... P>
    class xmaterialize final : public B<xmaterialize<B, P...>>
    {
    public:

        using self_type = xmaterialize<B, P...>;
        using base_type = B<self_type>;

        template <class... A>
        xmaterialize(A&&...);
        ~xmaterialize();

        xmaterialize(const xmaterialize&);
        xmaterialize& operator=(const xmaterialize&);

        xmaterialize(xmaterialize&&) = default;
        xmaterialize& operator=(xmaterialize&&) = default;

        const xmaterialize& finalize() const;
    };

    /*******************************
     * xmaterialize implementation *
     *******************************/

    template <template <class> class B, class... P>
    template <class... A>
    inline xmaterialize<B, P...>::xmaterialize(A&&... args)
        : base_type(std::forward<A>(args)...)
    {
        this->open();
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>::~xmaterialize()
    {
        if (!this->moved_from())
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
        this->close();
        base_type::operator=(rhs);
        this->open();
        return *this;
    }

    template <template <class> class B, class... P>
    inline const xmaterialize<B, P...>& xmaterialize<B, P...>::finalize() const
    {
        return *this;
    }
}

#endif
