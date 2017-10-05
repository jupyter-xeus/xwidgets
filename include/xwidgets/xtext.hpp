/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TEXT_HPP
#define XWIDGETS_TEXT_HPP

#include "xmaterialize.hpp"
#include "xstring.hpp"

namespace xw
{
    /********************
     * text declaration *
     ********************/

    template <class D>
    class xtext : public xstring<D>
    {
    public:

        using submit_callback_type = std::function<void()>;

        using base_type = xstring<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        void on_submit(submit_callback_type);

        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update, true);

        void handle_custom_message(const xeus::xjson&);

    protected:

        xtext();

    private:

        void set_defaults();

        std::list<submit_callback_type> m_submit_callbacks;
    };

    using text = xmaterialize<xtext>;

    using text_generator = xgenerator<xtext>;

    /************************
     * xtext implementation *
     ************************/

    template <class D>
    inline xeus::xjson xtext<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xtext<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
    }

    template <class D>
    inline void xtext<D>::on_submit(submit_callback_type cb)
    {
        m_submit_callbacks.emplace_back(std::move(cb));
    }

    template <class D>
    inline xtext<D>::xtext()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtext<D>::set_defaults()
    {
        this->_model_name() = "TextModel";
        this->_view_name() = "TextView";
    }

    template <class D>
    inline void xtext<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "submit")
        {
            for (auto it = m_submit_callbacks.begin(); it != m_submit_callbacks.end(); ++it)
            {
                it->operator()();
            }
        }
    }
}

#endif
