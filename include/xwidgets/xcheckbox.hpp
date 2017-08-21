/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_CHECKBOX_HPP
#define XWIDGETS_CHECKBOX_HPP

#include <string>

#include "xboolean.hpp"

namespace xeus
{
    /************************
     * checkbox declaration *
     ************************/

    template <class D>
    class xcheckbox : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        xcheckbox();
        xjson get_state() const;
        void apply_patch(const xjson& patch);


        XPROPERTY(bool, derived_type, indent, true);

    private:

        void set_defaults();
    };

    class checkbox final : public xcheckbox<checkbox>
    {
    public:

        using base_type = xcheckbox<checkbox>;

        checkbox()
            : base_type()
        {
            this->open();
        }

        ~checkbox()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        checkbox(const checkbox& other)
            : base_type(other)
        {
            this->open();
        }

        checkbox& operator=(const checkbox& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /****************************
     * xcheckbox implementation *
     ****************************/

    template <class D>
    inline xcheckbox<D>::xcheckbox()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xcheckbox<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(indent, state);

        return state;
    }

    template <class D>
    inline void xcheckbox<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(indent, patch)
    }

    template <class D>
    inline void xcheckbox<D>::set_defaults()
    {
        this->_model_name() = "CheckboxModel";
        this->_view_name() = "CheckboxView";
    }
}

#endif
