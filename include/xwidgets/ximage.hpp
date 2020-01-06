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

        void serialize_state(xeus::xjson& state, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::string, derived_type, format, "png");
        XTRAIT(std::string, derived_type, width, "");
        XTRAIT(std::string, derived_type, height, "");

    protected:

        ximage();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using image = xmaterialize<ximage>;

    using image_generator = xgenerator<ximage>;

    /*************************
     * ximage implementation *
     *************************/

    template <class D>
    inline void ximage<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(format, state, buffers);
        set_patch_from_property(width, state, buffers);
        set_patch_from_property(height, state, buffers);
    }

    template <class D>
    inline void ximage<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
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

    inline image_generator image_from_file(const std::string& filename)
    {
        return image_generator().value(read_file(filename));
    }

    inline image_generator image_from_url(const std::string& url)
    {
        std::vector<char> value(url.cbegin(), url.cend());
        return image_generator().value(value).format("url");
    }

    /**********************
     * custom serializers *
     **********************/

    inline void set_patch_from_property(const decltype(image::value)& property,
                                        xeus::xjson& patch,
                                        xeus::buffer_sequence& buffers)
    {
        patch[property.name()] = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.emplace_back(property().data(), property().size());
    }

    inline void set_property_from_patch(decltype(image::value)& property,
                                        const xeus::xjson& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(image::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            const char* value_buf = value_buffer.data<const char>();
            property = value_type(value_buf, value_buf + value_buffer.size());
        }
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<ximage>;
    extern template xmaterialize<ximage>::xmaterialize();
    extern template class xtransport<xmaterialize<ximage>>;
    extern template class xgenerator<ximage>;
    extern template xgenerator<ximage>::xgenerator();
    extern template class xtransport<xgenerator<ximage>>;
#endif
}
#endif
