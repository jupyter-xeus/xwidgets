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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::vector<std::string>, derived_type, tooltips);

        XTRAIT(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XTRAIT(bool, derived_type, readout, true);
        XTRAIT(bool, derived_type, continuous_update, true);

    protected:

        xselectionslider();

        template <class O, class T>
        xselectionslider(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using selectionslider = xmaterialize<xselectionslider>;

    using selectionslider_generator = xgenerator<xselectionslider>;

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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XTRAIT(std::vector<std::string>, derived_type, tooltips);

        XTRAIT(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XTRAIT(bool, derived_type, readout, true);
        XTRAIT(bool, derived_type, continuous_update, true);

    protected:

        xselection_rangeslider();
        xselection_rangeslider(options_type&& options);
        xselection_rangeslider(const options_type& options);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using selection_rangeslider = xmaterialize<xselection_rangeslider>;

    using selection_rangeslider_generator = xgenerator<xselection_rangeslider>;

    /***********************************
     * xselectionslider implementation *
     ***********************************/

    template <class D>
    inline void xselectionslider<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(orientation, state, buffers);
        set_patch_from_property(readout, state, buffers);
        set_patch_from_property(continuous_update, state, buffers);
    }

    template <class D>
    inline void xselectionslider<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(readout, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
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

        auto self = this->self();
        self->template validate<decltype(self->_options_labels)>([](auto&, auto& proposal) {
            if (proposal.empty())
            {
                throw std::runtime_error("Empty collection passed to selection slider");
            }
        });
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
    inline void xselection_rangeslider<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        set_patch_from_property(orientation, state, buffers);
        set_patch_from_property(readout, state, buffers);
        set_patch_from_property(continuous_update, state, buffers);
    }

    template <class D>
    inline void xselection_rangeslider<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(readout, patch, buffers);
        set_property_from_patch(continuous_update, patch, buffers);
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

        auto self = this->self();
        self->template validate<decltype(self->_options_labels)>([](auto&, auto& proposal) {
            if (proposal.empty())
            {
                throw std::runtime_error("Empty collection passed to selection slider");
            }
        });
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

        auto self = this->self();
        self->template validate<decltype(self->_options_labels)>([](auto&, auto& proposal) {
            if (proposal.empty())
            {
                throw std::runtime_error("Empty collection passed to selection slider");
            }
        });
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

#ifndef _WIN32
    extern template class xmaterialize<xselectionslider>;
    extern template xmaterialize<xselectionslider>::xmaterialize();
    extern template class xtransport<xmaterialize<xselectionslider>>;
    extern template class xgenerator<xselectionslider>;
    extern template xgenerator<xselectionslider>::xgenerator();
    extern template class xtransport<xgenerator<xselectionslider>>;

    extern template class xmaterialize<xselection_rangeslider>;
    extern template xmaterialize<xselection_rangeslider>::xmaterialize();
    extern template class xtransport<xmaterialize<xselection_rangeslider>>;
    extern template class xgenerator<xselection_rangeslider>;
    extern template xgenerator<xselection_rangeslider>::xgenerator();
    extern template class xtransport<xgenerator<xselection_rangeslider>>;
#endif
}
#endif
