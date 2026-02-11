/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_SELECTIONSLIDER_HPP
#define XWIDGETS_SELECTIONSLIDER_HPP

#include <string>
#include <utility>
#include <vector>

#include "xeither.hpp"
#include "xmaterialize.hpp"
#include "xselection.hpp"
#include "xslider.hpp"

namespace xw
{
    /*******************************
     * selectionslider declaration *
     *******************************/

    template <class D>
    class xselectionslider : public xselection<D>
    {
    public:

        using base_type = xselection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<std::string>, xcommon, tooltips);
        XPROPERTY(std::string, xcommon, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(bool, xcommon, readout, true);
        XPROPERTY(bool, xcommon, continuous_update, true);
        XPROPERTY(std::string, xcommon, behavior, "drag-tap", XEITHER("drag-tap", "drag-snap", "tap", "drag", "snap"));
        XPROPERTY(::xw::slider_style, xcommon, style);

    protected:

        xselectionslider();

        template <class O, class T>
        xselectionslider(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using selectionslider = xmaterialize<xselectionslider>;

    /*************************************
     * selection_rangeslider declaration *
     *************************************/

    template <class D>
    class xselection_rangeslider : public xmultiple_selection<D>
    {
    public:

        using base_type = xmultiple_selection<D>;
        using derived_type = D;
        using options_type = typename base_type::options_type;
        using value_type = typename base_type::value_type;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<std::string>, xcommon, tooltips);

        XPROPERTY(std::string, xcommon, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(bool, xcommon, readout, true);
        XPROPERTY(bool, xcommon, continuous_update, true);
        XPROPERTY(std::string, xcommon, behavior, "drag-tap", XEITHER("drag-tap", "drag-snap", "tap", "drag", "snap"));
        XPROPERTY(::xw::slider_style, xcommon, style);

    protected:

        xselection_rangeslider();
        xselection_rangeslider(options_type&& options);
        xselection_rangeslider(const options_type& options);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using selection_rangeslider = xmaterialize<xselection_rangeslider>;

    /***********************************
     * xselectionslider implementation *
     ***********************************/

    template <class D>
    inline void xselectionslider<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(orientation(), state["orientation"], buffers);
        xwidgets_serialize(readout(), state["readout"], buffers);
        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
        xwidgets_serialize(behavior(), state["behavior"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void xselectionslider<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xselectionslider<D>::xselectionslider()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class O, class T>
    inline xselectionslider<D>::xselectionslider(O&& options, T&& value)
        : base_type(std::forward<O>(options), std::forward<T>(value))
    {
        set_defaults();

        if (this->_options_labels().empty())
        {
            throw std::runtime_error("Empty collection passed to selection slider");
        }

        this->template validate<xcommon, options_type>(
            "_options_labels",
            [](auto&, auto& proposal)
            {
                if (proposal.empty())
                {
                    throw std::runtime_error("Empty collection passed to selection slider");
                }
            }
        );
    }

    template <class D>
    inline void xselectionslider<D>::set_defaults()
    {
        this->_model_name() = "SelectionSliderModel";
        this->_view_name() = "SelectionSliderView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*****************************************
     * xselection_rangeslider implementation *
     *****************************************/

    template <class D>
    inline void xselection_rangeslider<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(orientation(), state["orientation"], buffers);
        xwidgets_serialize(readout(), state["readout"], buffers);
        xwidgets_serialize(continuous_update(), state["continuous_update"], buffers);
        xwidgets_serialize(behavior(), state["behavior"], buffers);
        xwidgets_serialize(style(), state["style"], buffers);
    }

    template <class D>
    inline void
    xselection_rangeslider<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        this->apply_patch_to_registered_properties(patch, buffers);
    }

    template <class D>
    inline xselection_rangeslider<D>::xselection_rangeslider()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xselection_rangeslider<D>::xselection_rangeslider(options_type&& options)
        : base_type(std::move(options))
    {
        set_defaults();

        if (this->_options_labels().empty())
        {
            throw std::runtime_error("Empty collection passed to selection slider");
        }

        this->template validate<xcommon, options_type>(
            "value",
            [](auto&, auto& proposal)
            {
                if (proposal.empty())
                {
                    throw std::runtime_error("Empty collection passed to selection slider");
                }
            }
        );
    }

    template <class D>
    inline xselection_rangeslider<D>::xselection_rangeslider(const options_type& options)
        : base_type(options)
    {
        set_defaults();

        if (this->_options_labels().empty())
        {
            throw std::runtime_error("Empty collection passed to selection slider");
        }

        this->template validate<xcommon, options_type>(
            "_options_labels",
            [](auto&, auto& proposal)
            {
                if (proposal.empty())
                {
                    throw std::runtime_error("Empty collection passed to selection slider");
                }
            }
        );
    }

    template <class D>
    inline void xselection_rangeslider<D>::set_defaults()
    {
        this->index() = {0, 0};
        this->_model_name() = "SelectionRangeSliderModel";
        this->_view_name() = "SelectionRangeSliderView";
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_module_version() = XWIDGETS_CONTROLS_VERSION;
        this->_view_module_version() = XWIDGETS_CONTROLS_VERSION;
    }

    /*********************
     * precompiled types *
     *********************/

    extern template class xmaterialize<xselectionslider>;
    extern template class xtransport<xmaterialize<xselectionslider>>;

    extern template class xmaterialize<xselection_rangeslider>;
    extern template class xtransport<xmaterialize<xselection_rangeslider>>;
}
#endif
