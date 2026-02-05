/***************************************************************************
 * Copyright (c) 2018, Sylvain Corlay, Johan Mabille an                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_MEDIA_HPP
#define XWIDGETS_MEDIA_HPP

#include <cstddef>
#include <fstream>
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

        XPROPERTY(value_type, xcommon, value);

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
        this->buffer_paths() = {{"value"}};

        this->_model_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module() = "@jupyter-widgets/controls";
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_name() = {};
    }

    inline std::vector<char> read_file(const std::string& filename)
    {
        const char* cstr = filename.c_str();
        std::basic_ifstream<char> file(cstr, std::ios::binary);
        return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    /**********************
     * custom serializers *
     **********************/

    inline void set_property_from_patch(
        decltype(media::value)& property,
        const nl::json& patch,
        const xeus::buffer_sequence& buffers
    )
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(media::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            property = value_type(value_buffer.data(), value_buffer.data() + value_buffer.size());
        }
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xmedia>;
    extern template class xtransport<xmaterialize<xmedia>>;
}
#endif
