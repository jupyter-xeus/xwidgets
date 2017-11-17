/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_SELECTION_CONTAINER_HPP
#define XWIDGETS_SELECTION_CONTAINER_HPP

#include <string>
#include <vector>

#include "xtl/xoptional.hpp"

#include "xbox.hpp"
#include "xmaterialize.hpp"

namespace xw
{
    /************************************
     * xselection_container declaration *
     ************************************/

    template <class D>
    class xselection_container : public xbox<D>
    {
    public:

        using base_type = xbox<D>;
        using derived_type = D;

        using titles_type = std::vector<std::string>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(titles_type, derived_type, _titles);
        XPROPERTY(xtl::xoptional<int>, derived_type, selected_index, 0);

        void set_title(typename titles_type::size_type i, std::string title);

    protected:

        xselection_container();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /***************************************
     * xselection_container implementation *
     ***************************************/

    template <class D>
    inline xeus::xjson xselection_container<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(_titles, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(selected_index, state);

        return state;
    }

    template <class D>
    inline void xselection_container<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(_titles, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(selected_index, patch);
    }

    template <class D>
    inline xselection_container<D>::xselection_container()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xselection_container<D>::set_defaults()
    {
    }

    template <class D>
    inline void xselection_container<D>::set_title(typename titles_type::size_type i, std::string title)
    {
        if (_titles().size() != this->children().size())
        {
            _titles() = titles_type(this->children().size());
        }
        _titles()[i] = title;
        xeus::xjson state;
        XOBJECT_SET_PATCH_FROM_PROPERTY(_titles, state);
        this->send_patch(std::move(state));
    }
}

#endif
