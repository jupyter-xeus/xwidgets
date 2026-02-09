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

        XPROPERTY(std::string, xcommon, format, "mp4");
        XPROPERTY(std::string, xcommon, width, "");
        XPROPERTY(std::string, xcommon, height, "");
        XPROPERTY(bool, xcommon, autoplay, true);
        XPROPERTY(bool, xcommon, loop, true);
        XPROPERTY(bool, xcommon, controls, true);

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
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xvideo<D>::xvideo()
        : base_type()
    {
        set_defaults();
        REGISTER_PROPERTIES(format, width, height, autoplay, loop, controls);
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

    inline auto video_from_file(const std::string& filename)
    {
        return video::initialize().value(read_file(filename));
    }

    inline auto video_from_url(const std::string& url)
    {
        std::vector<char> value(url.cbegin(), url.cend());
        auto video_widget = video::initialize();
        video_widget.value = value;
        video_widget.format = "url";
        return video_widget;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xvideo>;
    extern template class xtransport<xmaterialize<xvideo>>;
}
#endif
