/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TOGGLE_HPP
#define XWIDGETS_TOGGLE_HPP

#include <string>

#include "xboolean.hpp"

namespace xeus
{
    /****************************
     * togglebutton declaration *
     ****************************/

    template <class D>
    class xtogglebutton : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        xtogglebutton();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(std::string, derived_type, tooltip);
        XPROPERTY(std::string, derived_type, icon);
        XPROPERTY(X_CASELESS_STR_ENUM(primary, success, info, warning, danger, ), derived_type, button_style);

    private:

        void set_defaults();
    };

    class togglebutton final : public xtogglebutton<togglebutton>
    {
    public:

        using base_type = xtogglebutton<togglebutton>;

        togglebutton()
            : base_type()
        {
            this->open();
        }

        ~togglebutton()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        togglebutton(const togglebutton& other)
            : base_type(other)
        {
            this->open();
        }

        togglebutton& operator=(const togglebutton& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /********************************
     * xtogglebutton implementation *
     ********************************/

    template <class D>
    inline xtogglebutton<D>::xtogglebutton()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xtogglebutton<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(tooltip, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(icon, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(button_style, state);

        return state;
    }

    template <class D>
    inline void xtogglebutton<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(tooltip, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(icon, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(button_style, patch)
    }

    template <class D>
    inline void xtogglebutton<D>::set_defaults()
    {
        this->_model_name() = "ToggleButtonModel";
        this->_view_name() = "ToggleButtonView";
    }
}

#endif
