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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(std::vector<std::string>, derived_type, tooltips);

        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(bool, derived_type, readout, true);
        XPROPERTY(bool, derived_type, continuous_update, true);

    protected:

        template <class O, class T>
        xselectionslider(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using selectionslider = xmaterialize<xselectionslider>;

    using selectionslider_generator = xgenerator<xselectionslider>;

    /***********************************
     * xselectionslider implementation *
     ***********************************/

    template <class D>
    inline xeus::xjson xselectionslider<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(readout, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xselectionslider<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(readout, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
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

        this->template validate<decltype(this->_options_labels)>([&](const auto&, auto& proposal) {
            if (proposal.empty())
            {
                throw std::runtime_error("Empty collection passed to selection slider");
            }
        });
    }

    template <class D>
    inline void xselectionslider<D>::set_defaults()
    {
        this->_model_module() = "@jupyter-widgets/controls";
        this->_view_module() = "@jupyter-widgets/controls";
        this->_model_name() = "SelectionSliderModel";
        this->_view_name() = "SelectionSliderView";
    }
}
#endif
