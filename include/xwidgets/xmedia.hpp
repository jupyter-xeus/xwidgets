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

        void serialize_state(xeus::xjson& state, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(value_type, derived_type, value);

        const std::vector<xjson_path_type>& buffer_paths() const;

    protected:

        xmedia();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using media = xmaterialize<xmedia>;

    using media_generator = xgenerator<xmedia>;

    /*************************
     * xmedia implementation *
     *************************/

    template <class D>
    inline void xmedia<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(value, state, buffers);
    }

    template <class D>
    inline void xmedia<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(value, patch, buffers);
    }

    template <class D>
    inline const std::vector<xjson_path_type>& xmedia<D>::buffer_paths() const
    {
        static const std::vector<xjson_path_type> default_buffer_paths = {{"value"}};
        return default_buffer_paths;
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

#ifndef _WIN32
    extern template class xmaterialize<xmedia>;
    extern template xmaterialize<xmedia>::xmaterialize();
    extern template class xtransport<xmaterialize<xmedia>>;
    extern template class xgenerator<xmedia>;
    extern template xgenerator<xmedia>::xgenerator();
    extern template class xtransport<xgenerator<xmedia>>;
#endif
}
#endif
