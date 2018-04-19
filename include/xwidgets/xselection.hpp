/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_SELECTION_HPP
#define XWIDGETS_SELECTION_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "xwidget.hpp"

namespace xw
{
    /**************************
     * xselection declaration *
     **************************/

    template <class D>
    class xselection : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        using options_type = std::vector<std::string>;
        using value_type = options_type::value_type;
        using index_type = options_type::size_type;

        XPROPERTY(index_type, derived_type, index);
        XPROPERTY(options_type, derived_type, _options_labels);

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(bool, derived_type, disabled, false);

        // non-synchronized properties
        XPROPERTY(value_type, derived_type, value);

    protected:

        xselection();

        template <class O, class T>
        xselection(O&& options, T&& value);

        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    /***********************************
     * xmultiple_selection declaration *
     ***********************************/

    template <class D>
    class xmultiple_selection : public xwidget<D>
    {
    public:

        using base_type = xwidget<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        using options_type = std::vector<std::string>;
        using value_type = options_type;
        using index_type = std::vector<options_type::size_type>;

        XPROPERTY(index_type, derived_type, index);
        XPROPERTY(options_type, derived_type, _options_labels);

        XPROPERTY(std::string, derived_type, description);
        XPROPERTY(bool, derived_type, disabled, false);

        // non-synchronized properties
        XPROPERTY(value_type, derived_type, value);

    protected:

        explicit xmultiple_selection();
        explicit xmultiple_selection(options_type&& options);
        explicit xmultiple_selection(const options_type& options);

        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    /*****************************
     * xselection implementation *
     *****************************/

    template <class D>
    inline void xselection<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(index, state, buffers);
        this->set_patch_from_property(_options_labels, state, buffers);
        this->set_patch_from_property(description, state, buffers);
        this->set_patch_from_property(disabled, state, buffers);
    }

    template <class D>
    inline void xselection<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(index, patch, buffers);
        this->set_property_from_patch(_options_labels, patch, buffers);
        this->set_property_from_patch(description, patch, buffers);
        this->set_property_from_patch(disabled, patch, buffers);
    }

    template <class D>
    inline xselection<D>::xselection()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    template <class O, class T>
    inline xselection<D>::xselection(O&& options, T&& v)
        : base_type()
    {
        set_defaults();

        this->_options_labels() = std::forward<O>(options);
        this->value() = std::forward<T>(v);

        this->setup_properties();
    }

    template <class D>
    inline void xselection<D>::setup_properties()
    {
        auto self = this->self();
        self->template observe<decltype(self->value)>([](auto& owner) {
            const options_type& opt = owner._options_labels();
            auto new_index = index_type(std::find(opt.cbegin(), opt.cend(), owner.value()) - opt.cbegin());
            if (new_index != owner.index())
            {
                owner.index = new_index;
            }
        });

        self->template observe<decltype(self->index)>([](auto& owner) {
            auto new_value = owner._options_labels()[owner.index()];
            if (new_value != owner.value())
            {
                owner.value = new_value;
            }
        });

        self->template observe<decltype(self->_options_labels)>([](auto& owner) {
            const options_type& opt = owner._options_labels();
            auto position = std::find(opt.cbegin(), opt.cend(), owner.value());
            if (position == opt.cend())
            {
                position = opt.cbegin();
            }
            owner.index = position - opt.cbegin();
        });

        self->template validate<decltype(self->value)>([](auto& owner, auto& proposal) {
            const options_type& opt = owner._options_labels();
            if (std::find(opt.cbegin(), opt.cend(), proposal) == opt.cend())
            {
                throw std::runtime_error("Invalid value");
            }
        });
    }

    template <class D>
    inline void xselection<D>::set_defaults()
    {
    }

    /**************************************
     * xmultiple_selection implementation *
     **************************************/

    template <class D>
    inline void xmultiple_selection<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        this->set_patch_from_property(index, state, buffers);
        this->set_patch_from_property(_options_labels, state, buffers);
        this->set_patch_from_property(description, state, buffers);
        this->set_patch_from_property(disabled, state, buffers);
    }

    template <class D>
    inline void xmultiple_selection<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        this->set_property_from_patch(index, patch, buffers);
        this->set_property_from_patch(_options_labels, patch, buffers);
        this->set_property_from_patch(description, patch, buffers);
        this->set_property_from_patch(disabled, patch, buffers);
    }

    template <class D>
    inline xmultiple_selection<D>::xmultiple_selection()
        : base_type()
    {
        set_defaults();
        this->setup_properties();
    }

    template <class D>
    inline xmultiple_selection<D>::xmultiple_selection(options_type&& options)
        : base_type()
    {
        set_defaults();
        this->_options_labels() = std::move(options);
        this->setup_properties();
    }

    template <class D>
    inline xmultiple_selection<D>::xmultiple_selection(const options_type& options)
        : base_type()
    {
        set_defaults();

        this->_options_labels() = options;
        this->setup_properties();
    }

    template <class D>
    inline void xmultiple_selection<D>::setup_properties()
    {
        auto self = this->self();
        self->template observe<decltype(self->value)>([](auto& owner) {
            const options_type& opt = owner._options_labels();
            index_type new_index;
            for (const auto& val : owner.value())
            {
                new_index.push_back(std::find(opt.cbegin(), opt.cend(), val) - opt.cbegin());
            }
            if (new_index != owner.index())
            {
                owner.index = new_index;
            }
        });

        self->template observe<decltype(self->index)>([](auto& owner) {
            value_type new_value;
            for (const auto& i : owner.index())
            {
                new_value.push_back(owner._options_labels()[i]);
            }
            if (new_value != owner.value())
            {
                owner.value = new_value;
            }
        });

        self->template observe<decltype(self->_options_labels)>([](auto& owner) {
            owner.index = index_type();
        });

        self->template validate<decltype(self->value)>([](auto& owner, auto& proposal) {
            const options_type& opt = owner._options_labels();
            for (const auto& val : proposal)
            {
                if (std::find(opt.cbegin(), opt.cend(), val) == opt.cend())
                {
                    throw std::runtime_error("Invalid value");
                }
            }
        });
    }

    template <class D>
    inline void xmultiple_selection<D>::set_defaults()
    {
    }
}
#endif
