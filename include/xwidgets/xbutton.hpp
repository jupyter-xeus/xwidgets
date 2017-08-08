#ifndef XBUTTON_HPP
#define XBUTTON_HPP

#include "xwidget.hpp"

namespace xeus
{
    class xbutton final : public xwidget<xbutton>
    {
    public:

        using click_callback_type = std::function<void()>;

        using base_type = xwidget<xbutton>;

        xbutton();

        xjson get_state() const;
        void set_state(const xjson& state);

        void on_click(std::function<void()>);

    private:

        void handle_button_message(const xjson&);
        void set_defaults();

        std::list<click_callback_type> m_click_callbacks;
    };

    /**************************
     * xbutton implementation *
     **************************/

    inline xbutton::xbutton()
        : base_type()
    {
        set_defaults();
        this->on_message(std::bind(&xbutton::handle_button_message, this, _1));
        this->open();
    }

    inline xjson xbutton::get_state() const
    {
        return base_type::get_state();
    }

    inline void xbutton::set_state(const xjson& state)
    {
    }

    inline void xbutton::on_click(click_callback_type cb)
    {
        m_click_callbacks.emplace_back(std::move(cb));
    }

    inline void xbutton::set_defaults()
    {
        base_type::_model_module() = "@jupyter-widgets/controls";
        base_type::_view_module() = "@jupyter-widgets/controls";
        base_type::_model_name() = "ButtonModel";
        base_type::_view_name() = "ButtonView";
    }

    inline void xbutton::handle_button_message(const xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "click")
        {
            for (auto it = m_click_callbacks.begin(); it != m_click_callbacks.end(); ++it)
            {
                it->operator()();
            }
        }
    }
}
#endif

