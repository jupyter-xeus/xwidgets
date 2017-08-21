/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TEXTAREA_HPP
#define XWIDGETS_TEXTAREA_HPP

#include "xstring.hpp"

namespace xeus
{
    /************************
     * textarea declaration *
     ************************/

    template <class D>
    class xtextarea : public xstring<D>
    {
    public:

        using base_type = xstring<D>;
        using derived_type = D;

        xtextarea();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(XOPTIONAL(int), derived_type, rows);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update, true);

    private:

        void set_defaults();
    };

    class textarea final : public xtextarea<textarea>
    {
    public:

        using base_type = xtextarea<textarea>;

        textarea()
            : base_type()
        {
            this->open();
        }

        ~textarea()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        textarea(const textarea& other)
            : base_type(other)
        {
            this->open();
        }

        textarea& operator=(const textarea& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }
    };

    /****************************
     * xtextarea implementation *
     ****************************/

    template <class D>
    inline xtextarea<D>::xtextarea()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xtextarea<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(rows, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xtextarea<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(rows, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch)
    }

    template <class D>
    inline void xtextarea<D>::set_defaults()
    {
        this->_model_name() = "TextareaModel";
        this->_view_name() = "TextareaView";
    }
}

#endif
