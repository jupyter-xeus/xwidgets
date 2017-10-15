/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_FACTORY_HPP
#define XWIDGETS_FACTORY_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include "xmaterialize.hpp"
#include "xregistry.hpp"

namespace xw
{
    /*******************
     * xmaker template *
     *******************/

    template <template <class> class CRTP, class... P>
    void xmaker(xeus::xcomm&& comm, const xeus::xjson& state)
    {
        auto model = xgenerator<CRTP, P...>(std::move(comm), true);
        model.apply_patch(state);
        get_transport_registry().register_owning(reinterpret_cast<xmaterialize<CRTP, P...>&&>(model));
    }

    /************************
     * xfactory declaration *
     ************************/

    class xfactory
    {
    public:

        using maker_type = std::function<void(xeus::xcomm&&, const xeus::xjson&)>;

        void register_maker(const std::string& model_module,
                            const std::string& model_name,
                            const std::string& view_module,
                            const std::string& view_name,
                            maker_type maker);

        void make(xeus::xcomm&& comm, const xeus::xjson& state) const;

    private:

        std::unordered_map<std::string, maker_type> m_makers;
    };

    inline xfactory& get_xfactory();

    /***************************
     * xfactory implementation *
     ***************************/

    inline void xfactory::register_maker(const std::string& model_module,
                                         const std::string& model_name,
                                         const std::string& view_module,
                                         const std::string& view_name,
                                         maker_type maker)
    {
        m_makers[model_module + model_name + view_module + view_name] = std::move(maker);
    }

    inline void xfactory::make(xeus::xcomm&& comm, const xeus::xjson& state) const
    {
        std::string model_module = state["_model_module"];
        std::string model_name = state["_model_name"];
        std::string view_module = state["_view_module"];
        std::string view_name = state["_view_name"];
        m_makers.at(model_module + model_name + view_module + view_name)(std::move(comm), state);
    }

    inline xfactory& get_xfactory()
    {
        static xfactory factory;
        return factory;
    }
}

#endif
