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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

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
    inline xeus::xjson xselection<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(index, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_options_labels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(description, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);

        return state;
    }

    template <class D>
    inline void xselection<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(index, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(_options_labels, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(description, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch);
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
        this->template observe<decltype(value)>([this]() {
            const options_type& opt = this->_options_labels();
            auto new_index = std::find(opt.cbegin(), opt.cend(), this->value()) - opt.cbegin();
            if (new_index != this->index())
            {
                this->index = new_index;
            }
        });

        this->template observe<decltype(index)>([this]() {
            auto new_value = this->_options_labels()[this->index()];
            if (new_value != this->value())
            {
                this->value = new_value;
            }
        });

        this->template observe<decltype(_options_labels)>([this]() {
            const options_type& opt = this->_options_labels();
            auto position = std::find(opt.cbegin(), opt.cend(), this->value());
            if (position == opt.cend())
            {
                position = opt.cbegin();
            }
            this->index = position - opt.cbegin();
        });

        this->template validate<decltype(value)>([](auto& proposal) {
            const options_type& opt = this->_options_labels();
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
    inline xeus::xjson xmultiple_selection<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(index, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(_options_labels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(description, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(disabled, state);

        return state;
    }

    template <class D>
    inline void xmultiple_selection<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(index, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(_options_labels, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(description, patch)
        XOBJECT_SET_PROPERTY_FROM_PATCH(disabled, patch)
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
        this->template observe<decltype(value)>([this]() {
            const options_type& opt = this->_options_labels();
            index_type new_index;
            for (const auto& val : this->value())
            {
                new_index.push_back(std::find(opt.cbegin(), opt.cend(), val) - opt.cbegin());
            }
            if (new_index != this->index())
            {
                this->index = new_index;
            }
        });

        this->template observe<decltype(index)>([this]() {
            value_type new_value;
            for (const auto& i : this->index())
            {
                new_value.push_back(this->_options_labels()[i]);
            }
            if (new_value != this->value())
            {
                this->value = new_value;
            }
        });

        this->template observe<decltype(_options_labels)>([this]() {
            this->index = index_type();
        });

        this->template validate<decltype(value)>([](auto& proposal) {
            const options_type& opt = this->_options_labels();
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
