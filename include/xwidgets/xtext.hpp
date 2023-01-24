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
#include "xstyle.hpp"

namespace xw
{
    /********************************
     *  text_style declaration  *
     ********************************/

    template <class D>
    class xtext_style : public xstyle<D>
    {
    public:

        using base_type = xstyle<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<std::string>, derived_type, background);
        XPROPERTY(std::string, derived_type, description_width);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, font_size);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, text_color);

    protected:

        xtext_style();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using text_style = xmaterialize<xtext_style>;

    /********************
     * text declaration *
     ********************/

    template <class D>
    class xtext : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        using submit_callback_type = std::function<void()>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_submit(submit_callback_type);

        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update, true);
        XPROPERTY(::xw::text_style, derived_type, style);

        void handle_custom_message(const nl::json&);

    protected:

        xtext();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<submit_callback_type> m_submit_callbacks;
    };

    using text = xmaterialize<xtext>;

    /**********************************
     * xtext_style implementation *
     **********************************/

    template <class D>
    inline void xtext_style<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(background(), state["background"], buffers);
        xwidgets_serialize(description_width(), state["description_width"], buffers);
        xwidgets_serialize(font_size(), state["font_size"], buffers);
        xwidgets_serialize(text_color(), state["text_color"], buffers);
    }

    template <class D>
    inline void xtext_style<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(background, patch, buffers);
        set_property_from_patch(description_width, patch, buffers);
        set_property_from_patch(font_size, patch, buffers);
        set_property_from_patch(text_color, patch, buffers);
    }

    template <class D>
    inline xtext_style<D>::xtext_style()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtext_style<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_name() = "TextStyleModel";
    }

    /************************
     * xtext implementation *
     ************************/

    template <class D>
    inline void xtext<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(disabled(), state["disabled"], buffers);
        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xtext<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(disabled, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
        set_property_from_patch(style, patch, buffers);
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
    inline void xtext<D>::handle_custom_message(const nl::json& content)
    {
        auto const event_it = content.find("event");
        if (event_it != content.end() && event_it.value() == "submit")
        {
            for (auto& callback : m_submit_callbacks)
            {
                callback();
            }
        }
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xtext>;
    extern template class xtransport<xmaterialize<xtext>>;

    extern template class xmaterialize<xtext_style>;
    extern template class xtransport<xmaterialize<xtext_style>>;
}

#endif
