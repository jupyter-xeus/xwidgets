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

#include "xeus/xjson.hpp"
#include "xwidgets_config.hpp"

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
        ~xmaterialize();

        xmaterialize(const xmaterialize&);
        xmaterialize& operator=(const xmaterialize&);

        xmaterialize(xmaterialize&&);
        xmaterialize& operator=(xmaterialize&&);
    };

    /**************************
     * xgenerator declaration *
     **************************/

    template <template <class> class B, class... P>
    class xgenerator final : public B<xgenerator<B, P...>>
    {
    public:

        using self_type = xgenerator<B, P...>;
        using base_type = B<self_type>;

        template <class... A>
        xgenerator(A&&...);

        xgenerator(const xgenerator&);
        xgenerator& operator=(const xgenerator&);

        xgenerator(xgenerator&&);
        xgenerator& operator=(xgenerator&&);

        xmaterialize<B, P...> finalize() &&;
    };

    /******************
     * xconcrete_type *
     ******************/

    template <class D>
    struct xconcrete_type
    {
        using type = D;
    };

    template <template <class> class B, class... P>
    struct xconcrete_type<xgenerator<B, P...>>
    {
        using type = xmaterialize<B, P...>;
    };

    template <class D>
    using xconcrete_type_t = typename xconcrete_type<D>::type;

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
    inline xmaterialize<B, P...>::xmaterialize(xmaterialize&&) = default;

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...>& xmaterialize<B, P...>::operator=(xmaterialize&& rhs) = default;

    /*****************************
     * xgenerator implementation *
     *****************************/

    template <template <class> class B, class... P>
    template <class... A>
    inline xgenerator<B, P...>::xgenerator(A&&... args)
        : base_type(std::forward<A>(args)...)
    {
    }

    template <template <class> class B, class... P>
    inline xmaterialize<B, P...> xgenerator<B, P...>::finalize() &&
    {
        return reinterpret_cast<typename xmaterialize<B, P...>::base_type&&>(*this);
    }

    template <template <class> class B, class... P>
    inline xgenerator<B, P...>::xgenerator(const xgenerator&) = default;

    template <template <class> class B, class... P>
    inline xgenerator<B, P...>& xgenerator<B, P...>::operator=(const xgenerator&) = default;

    template <template <class> class B, class... P>
    inline xgenerator<B, P...>::xgenerator(xgenerator&&) = default;

    template <template <class> class B, class... P>
    inline xgenerator<B, P...>& xgenerator<B, P...>::operator=(xgenerator&&) = default;

    /**********************************************************
     * Specialization of mime_bundle_repr for Jupyter Widgets *
     **********************************************************/

    template <template <class> class B, class... P>
    xeus::xjson mime_bundle_repr(const xmaterialize<B, P...>& val)
    {
        xeus::xjson mime_bundle;

        // application/vnd.jupyter.widget-view+json
        xeus::xjson widgets_json;
        widgets_json["version_major"] = XWIDGETS_PROTOCOL_VERSION_MAJOR;
        widgets_json["version_minor"] = XWIDGETS_PROTOCOL_VERSION_MINOR;
        widgets_json["model_id"] = val.id();
        mime_bundle["application/vnd.jupyter.widget-view+json"] = std::move(widgets_json);

        // text/plain
        mime_bundle["text/plain"] = "A Jupyter widget";
        return mime_bundle;
    }
}

#endif
