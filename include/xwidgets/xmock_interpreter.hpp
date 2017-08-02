/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XMOCK_INTERPRETER_HPP
#define XMOCK_INTERPRETER_HPP

#include "xeus/xinterpreter.hpp"

namespace xeus
{

#ifdef STANDALONE_WIDGETS

    xinterpreter& get_interpreter();

    class xmock_interpreter : public xinterpreter
    {

    public:

        using base_type = xinterpreter;

        xmock_interpreter();
        virtual ~xmock_interpreter() = default;

        xmock_interpreter(const xmock_interpreter&) = delete;
        xmock_interpreter& operator=(const xmock_interpreter&) = delete;

        xmock_interpreter(xmock_interpreter&&) = delete;
        xmock_interpreter& operator=(xmock_interpreter&&) = delete;

    private:

        void configure_impl() override {}

        xjson execute_request_impl(int execution_counter,
            const std::string& code,
            bool silent,
            bool store_history,
            const xjson_node* user_expressions,
            bool allow_stdin) override { return xjson(); }

        xjson complete_request_impl(const std::string& code,
            int cursor_pos) override { return xjson(); }

        xjson inspect_request_impl(const std::string& code,
            int cursor_pos,
            int detail_level) override { return xjson(); }

        xjson history_request_impl(const xhistory_arguments& args) override { return xjson(); }

        xjson is_complete_request_impl(const std::string& code) override { return xjson(); }

        xjson kernel_info_request_impl() { return xjson(); }

        void input_reply_impl(const std::string& value) {}

        xcomm_manager m_comm_manager;
    };

    inline xinterpreter& get_interpreter()
    {
        static xmock_interpreter interpreter;
        return interpreter;
    }

    inline xmock_interpreter::xmock_interpreter()
        : base_type(), m_comm_manager(nullptr)
    {
        base_type::register_publisher(base_type::publisher_type());
        base_type::register_stdin_sender(base_type::stdin_sender_type());
        base_type::register_comm_manager(&m_comm_manager);
    }

#endif //STANDALONE_WIDGET

}

#endif

