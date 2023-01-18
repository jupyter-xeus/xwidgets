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

#include "xbox.hpp"
#include "xmaterialize.hpp"
#include "xtl/xoptional.hpp"

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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
    inline void xselection_container<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(_titles(), state["_titles"], buffers);
        xwidgets_serialize(selected_index(), state["selected_index"], buffers);
    }

    template <class D>
    inline void
    xselection_container<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(_titles, patch, buffers);
        set_property_from_patch(selected_index, patch, buffers);
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

        nl::json state;
        xeus::buffer_sequence buffers;
        xwidgets_serialize(_titles(), state["_titles"], buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }
}

#endif
