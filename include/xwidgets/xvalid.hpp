/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_VALID_HPP
#define XWIDGETS_VALID_HPP

#include <string>

#include "xboolean.hpp"

namespace xeus
{
    /*********************
     * valid declaration *
     *********************/

    template <class D>
    class xvalid : public xboolean<D>
    {
    public:

        using base_type = xboolean<D>;
        using derived_type = D;

        xvalid();
        xjson get_state() const;
        void apply_patch(const xjson& patch);

        XPROPERTY(std::string, derived_type, readout, "Invalid");

    private:

        void set_defaults();
    };

    class valid final : public xvalid<valid>
    {
    public:

        using base_type = xvalid<valid>;

        valid()
            : base_type()
        {
            this->open();
        }

        ~valid()
        {
            if (!this->moved_from())
            {
                this->close();
            }
        }

        valid(const valid& other)
            : base_type(other)
        {
            this->open();
        }

        valid& operator=(const valid& other)
        {
            base_type::operator=(other);
            this->open();
            return *this;
        }

        valid(valid&&) = default;
        valid& operator=(valid&&) = default;
    };

    /*************************
     * xvalid implementation *
     *************************/

    template <class D>
    inline xvalid<D>::xvalid()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xjson xvalid<D>::get_state() const
    {
        xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(readout, state);

        return state;
    }

    template <class D>
    inline void xvalid<D>::apply_patch(const xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(readout, patch)
    }

    template <class D>
    inline void xvalid<D>::set_defaults()
    {
        this->_model_name() = "ValidModel";
        this->_view_name() = "ValidView";
    }
}

#endif
