/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_VIDEO_HPP
#define XWIDGETS_VIDEO_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "xmaterialize.hpp"
#include "xmedia.hpp"

namespace xw
{
    /*********************
     * video declaration *
     *********************/

    template <class D>
    class xvideo : public xmedia<D>
    {
    public:

        using base_type = xmedia<D>;
        using derived_type = D;

        void serialize_state(nl::json& state, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, format, "mp4");
        XPROPERTY(std::string, derived_type, width, "");
        XPROPERTY(std::string, derived_type, height, "");
        XPROPERTY(bool, derived_type, autoplay, true);
        XPROPERTY(bool, derived_type, loop, true);
        XPROPERTY(bool, derived_type, controls, true);

    protected:

        xvideo();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using video = xmaterialize<xvideo>;

    /*************************
     * xvideo implementation *
     *************************/

    template <class D>
    inline void xvideo<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(format(), state["format"], buffers);
        xwidgets_serialize(width(), state["width"], buffers);
        xwidgets_serialize(height(), state["height"], buffers);
        xwidgets_serialize(autoplay(), state["autoplay"], buffers);
        xwidgets_serialize(loop(), state["loop"], buffers);
        xwidgets_serialize(controls(), state["controls"], buffers);
    }

    template <class D>
    inline void xvideo<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(width, patch, buffers);
        set_property_from_patch(height, patch, buffers);
        set_property_from_patch(autoplay, patch, buffers);
        set_property_from_patch(loop, patch, buffers);
        set_property_from_patch(controls, patch, buffers);
    }

    template <class D>
    inline xvideo<D>::xvideo()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvideo<D>::set_defaults()
    {
        this->_model_name() = "VideoModel";
        this->_view_name() = "VideoView";
    }

    /**********************
     * custom serializers *
     **********************/

    inline void set_property_from_patch(decltype(video::value)& property,
                                        const nl::json& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(video::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            const char* value_buf = value_buffer.data<const char>();
            property = value_type(value_buf, value_buf + value_buffer.size());
        }
    }

    inline auto video_from_file(const std::string& filename)
    {
        return video::initialize().value(read_file(filename));
    }

    inline auto video_from_url(const std::string& url)
    {
        std::vector<char> value(url.cbegin(), url.cend());
        return video::initialize().value(value).format("url");
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xvideo>;
    extern template xmaterialize<xvideo>::xmaterialize();
    extern template class xtransport<xmaterialize<xvideo>>;
#endif
}
#endif
