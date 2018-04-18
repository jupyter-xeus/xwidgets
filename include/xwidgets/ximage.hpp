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
#include "xwidget.hpp"

namespace xw
{
    /**********************
     * custom serializers *
     **********************/

    inline void serialize_value(const std::vector<char>& value,
                                xeus::xjson& patch,
                                xeus::buffer_sequence& buffers,
                                const std::string& name)
    {
        patch[name] = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.emplace_back(value.data(), value.size());
    }

    inline void deserialize_value(std::vector<char>& value,
                                  const xeus::xjson& j,
                                  const xeus::buffer_sequence& buffers)
    {
        std::size_t buffer_index = detail::buffer_index(j.template get<std::string>());
        const auto& value_buffer = buffers[buffer_index];
        const char* value_buf = value_buffer.data<const char>();
        value = std::vector<char>(value_buf, value_buf + value_buffer.size());
    }

    /*********************
     * image declaration *
     *********************/

    template <class D>
    class ximage : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        using value_type = std::vector<char>;

        void serialize_state(xeus::xjson& state, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, format, "png");
        XPROPERTY(std::string, derived_type, width, "");
        XPROPERTY(std::string, derived_type, height, "");
        XPROPERTY(value_type, derived_type, value);

        const std::vector<xjson_path_type>& buffer_paths() const;

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
        set_patch_from_property(value, state, buffers);
    }

    template <class D>
    inline void ximage<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(width, patch, buffers);
        set_property_from_patch(height, patch, buffers);
        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline const std::vector<xjson_path_type>& ximage<D>::buffer_paths() const
    {
        static const std::vector<xjson_path_type> default_buffer_paths = {{"value"}};
        return default_buffer_paths;
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
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
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
