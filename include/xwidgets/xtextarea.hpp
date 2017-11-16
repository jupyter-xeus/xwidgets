/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_TEXTAREA_HPP
#define XWIDGETS_TEXTAREA_HPP

#include "xmaterialize.hpp"
#include "xstring.hpp"

namespace xw
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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(xtl::xoptional<int>, derived_type, rows);
        XPROPERTY(bool, derived_type, disabled);
        XPROPERTY(bool, derived_type, continuous_update, true);

    protected:

        xtextarea();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using textarea = xmaterialize<xtextarea>;
    using textarea_generator = xgenerator<xtextarea>;

    /****************************
     * xtextarea implementation *
     ****************************/

    template <class D>
    inline xeus::xjson xtextarea<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(rows, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(continuous_update, state);

        return state;
    }

    template <class D>
    inline void xtextarea<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(rows, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(continuous_update, patch);
    }

    template <class D>
    inline xtextarea<D>::xtextarea()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtextarea<D>::set_defaults()
    {
        this->_model_name() = "TextareaModel";
        this->_view_name() = "TextareaView";
    }
}

#endif
