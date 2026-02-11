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

        XPROPERTY(std::string, xcommon, format, "png");
        XPROPERTY(std::string, xcommon, width, "");
        XPROPERTY(std::string, xcommon, height, "");

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
        this->apply_patch_to_registered_properties(patch, buffers);
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
        auto image_widget = image::initialize();
        image_widget.value = value;
        image_widget.format = "url";
        return image_widget;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<ximage>;
    extern template class xtransport<xmaterialize<ximage>>;
}
#endif
