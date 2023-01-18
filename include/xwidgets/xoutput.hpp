/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_OUTPUT_HPP
#define XWIDGETS_OUTPUT_HPP

#include <string>

#include "xholder.hpp"
#include "xmaterialize.hpp"
#include "xwidget.hpp"

namespace xw
{
    /**********************
     * output declaration *
     **********************/

    template <class O>
    class output_guard;

    template <class D>
    class xoutput : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, msg_id);
        XPROPERTY(std::vector<nl::json>, derived_type, outputs);

        void capture();
        void release();
        output_guard<D> guard();

    protected:

        xoutput();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using output = xmaterialize<xoutput>;

    template <class O>
    class output_guard
    {
    public:

        explicit output_guard(const xoutput<O>& out);
        ~output_guard();

    private:

        xholder m_out;
    };

    /**************************
     * xoutput implementation *
     **************************/

    template <class D>
    inline void xoutput<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(msg_id(), state["msg_id"], buffers);
        xwidgets_serialize(outputs(), state["outputs"], buffers);
    }

    template <class D>
    inline void xoutput<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(msg_id, patch, buffers);
        set_property_from_patch(outputs, patch, buffers);
    }

    template <class D>
    inline xoutput<D>::xoutput()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xoutput<D>::set_defaults()
    {
        this->_model_name() = "OutputModel";
        this->_view_name() = "OutputView";
        this->_view_module() = "@jupyter-widgets/output";
        this->_model_module() = "@jupyter-widgets/output";
    }

    template <class D>
    inline void xoutput<D>::capture()
    {
        const auto& parent_header = xeus::get_interpreter().parent_header();
        if (parent_header.find("msg_id") != parent_header.end())
        {
            msg_id = parent_header["msg_id"].get<std::string>();
        }
    }

    template <class D>
    inline void xoutput<D>::release()
    {
        msg_id = "";
    }

    template <class D>
    inline output_guard<D> xoutput<D>::guard()
    {
        return output_guard<D>(*this);
    }

    template <class O>
    inline output_guard<O>::output_guard(const xoutput<O>& out)
        : m_out(make_id_holder(out.id()))
    {
        m_out.template get<O>().capture();
    }

    template <class O>
    inline output_guard<O>::~output_guard()
    {
        m_out.template get<O>().release();
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xoutput>;
    extern template class xtransport<xmaterialize<xoutput>>;
}
#endif
