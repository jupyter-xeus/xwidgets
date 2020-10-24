/***************************************************************************
* Copyright (c) 2018, Sylvain Corlay, Johan Mabille an                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_MEDIA_HPP
#define XWIDGETS_MEDIA_HPP

#include <fstream>
#include <cstddef>
#include <string>
#include <vector>

#include "xmaterialize.hpp"
#include "xwidget.hpp"

namespace xw
{
    /*********************
     * media declaration *
     *********************/

    template <class D>
    class xmedia : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        using value_type = std::vector<char>;

        void serialize_state(nl::json& state, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, value);

    protected:

        xmedia();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using media = xmaterialize<xmedia>;

    /*************************
     * xmedia implementation *
     *************************/

    inline void xwidgets_serialize(const std::vector<char>& value, nl::json& j, xeus::buffer_sequence& buffers)
    {
        j = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.emplace_back(value.data(), value.size());
    }

    template <class D>
    inline void xmedia<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(value(), state["value"], buffers);
    }

    template <class D>
    inline void xmedia<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline xmedia<D>::xmedia()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmedia<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    inline std::vector<char> read_file(const std::string& filename)
    {
        const char* cstr = filename.c_str();
        std::basic_ifstream<char> file(cstr, std::ios::binary);
        return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xmedia>;
    extern template class xtransport<xmaterialize<xmedia>>;
}
#endif
