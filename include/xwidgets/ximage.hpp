/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_IMAGE_HPP
#define XWIDGETS_IMAGE_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "xmaterialize.hpp"
#include "xmedia.hpp"

namespace xw
{
    /*********************
     * image declaration *
     *********************/

    template <class D>
    class ximage : public xmedia<D>
    {
    public:

        using base_type = xmedia<D>;
        using derived_type = D;

        void serialize_state(nl::json& state, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, format, "png");
        XPROPERTY(std::string, derived_type, width, "");
        XPROPERTY(std::string, derived_type, height, "");

    protected:

        ximage();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using image = xmaterialize<ximage>;

    /*************************
     * ximage implementation *
     *************************/

    template <class D>
    inline void ximage<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(format(), state["format"], buffers);
        xwidgets_serialize(width(), state["width"], buffers);
        xwidgets_serialize(height(), state["height"], buffers);
    }

    template <class D>
    inline void ximage<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(width, patch, buffers);
        set_property_from_patch(height, patch, buffers);
    }

    template <class D>
    inline ximage<D>::ximage()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void ximage<D>::set_defaults()
    {
        this->_model_name() = "ImageModel";
        this->_view_name() = "ImageView";
    }

    inline auto image_from_file(const std::string& filename)
    {
        return image::initialize().value(read_file(filename));
    }

    inline auto image_from_url(const std::string& url)
    {
        std::vector<char> value(url.cbegin(), url.cend());
        return image::initialize().value(value).format("url");
    }

    /**********************
     * custom serializers *
     **********************/

    inline void set_property_from_patch(decltype(image::value)& property,
                                        const nl::json& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(image::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            property = value_type(value_buffer.data(), value_buffer.data() + value_buffer.size());
        }
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<ximage>;
    extern template class xtransport<xmaterialize<ximage>>;
}
#endif
