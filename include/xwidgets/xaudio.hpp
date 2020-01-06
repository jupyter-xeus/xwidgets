/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_AUDIO_HPP
#define XWIDGETS_AUDIO_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "xmaterialize.hpp"
#include "xmedia.hpp"

namespace xw
{
    /*********************
     * audio declaration *
     *********************/

    template <class D>
    class xaudio : public xmedia<D>
    {
    public:

        using base_type = xmedia<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson& state, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::string, derived_type, format, "mp4");
        XTRAIT(bool, derived_type, autoplay, true);
        XTRAIT(bool, derived_type, loop, true);
        XTRAIT(bool, derived_type, controls, true);

    protected:

        xaudio();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using audio = xmaterialize<xaudio>;

    using audio_generator = xgenerator<xaudio>;

    /*************************
     * xaudio implementation *
     *************************/

    template <class D>
    inline void xaudio<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(format, state, buffers);
        set_patch_from_property(autoplay, state, buffers);
        set_patch_from_property(loop, state, buffers);
        set_patch_from_property(controls, state, buffers);
    }

    template <class D>
    inline void xaudio<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(autoplay, patch, buffers);
        set_property_from_patch(loop, patch, buffers);
        set_property_from_patch(controls, patch, buffers);
    }

    template <class D>
    inline xaudio<D>::xaudio()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xaudio<D>::set_defaults()
    {
        this->_model_name() = "AudioModel";
        this->_view_name() = "AudioView";
    }

    /**********************
     * custom serializers *
     **********************/

    inline void set_patch_from_property(const decltype(audio::value)& property,
                                        xeus::xjson& patch,
                                        xeus::buffer_sequence& buffers)
    {
        patch[property.name()] = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.emplace_back(property().data(), property().size());
    }

    inline void set_property_from_patch(decltype(audio::value)& property,
                                        const xeus::xjson& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(audio::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            const char* value_buf = value_buffer.data<const char>();
            property = value_type(value_buf, value_buf + value_buffer.size());
        }
    }

    inline audio_generator audio_from_file(const std::string& filename)
    {
        return audio_generator().value(read_file(filename));
    }

    inline audio_generator audio_from_url(const std::string& url)
    {
        std::vector<char> value(url.cbegin(), url.cend());
        return audio_generator().value(value).format("url");
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xaudio>;
    extern template xmaterialize<xaudio>::xmaterialize();
    extern template class xtransport<xmaterialize<xaudio>>;
    extern template class xgenerator<xaudio>;
    extern template xgenerator<xaudio>::xgenerator();
    extern template class xtransport<xgenerator<xaudio>>;
#endif
}
#endif
