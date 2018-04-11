/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_RADIOBUTTONS_HPP
#define XWIDGETS_RADIOBUTTONS_HPP

#include <utility>

#include "xmaterialize.hpp"
#include "xselection.hpp"

namespace xw
{
    /****************************
     * radiobuttons declaration *
     ****************************/

    template <class D>
    class xradiobuttons : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

    protected:

        xradiobuttons();

        template <class O, class T>
        xradiobuttons(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using radiobuttons = xmaterialize<xradiobuttons>;

    using radiobuttons_generator = xgenerator<xradiobuttons>;

    /********************************
     * xradiobuttons implementation *
     ********************************/

    template <class D>
    inline void xradiobuttons<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xradiobuttons<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xradiobuttons<D>::xradiobuttons()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class O, class T>
    inline xradiobuttons<D>::xradiobuttons(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();
    }

    template <class D>
    inline void xradiobuttons<D>::set_defaults()
    {
        this->_model_name() = "RadioButtonsModel";
        this->_view_name() = "RadioButtonsView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

#ifndef _WIN32
    extern template class xmaterialize<xradiobuttons>;
    extern template xmaterialize<xradiobuttons>::xmaterialize();
    extern template class xtransport<xmaterialize<xradiobuttons>>;
    extern template class xgenerator<xradiobuttons>;
    extern template xgenerator<xradiobuttons>::xgenerator();
    extern template class xtransport<xgenerator<xradiobuttons>>;
#endif
}
#endif
