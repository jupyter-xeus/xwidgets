/***************************************************************************
 * Copyright (c) 2022, QuantStack and XWidgets contributors                 *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#include <algorithm>
#include <array>
#include <exception>
#include <fstream>
#include <iterator>
#include <map>

#include <doctest/doctest.h>
#include <nlohmann/json-schema.hpp>
#include <xeus/xmessage.hpp>
#include <xwidgets/xall.hpp>

namespace xw
{
    namespace nl = nlohmann;

    nl::json read_models(const char* file);
    std::map<std::string, nl::json> models_to_schemas(nl::json const& models);
    void validate_schema(nl::json const& schema, nl::json const& obj);
    template <typename Widget>
    nl::json serialize();
    template <typename Widget>
    std::string model_name();

#ifndef XWIDGETS_MODELS_FILE
#error "XWIDGETS_MODELS_FILE must be defined pointing to model file"
#endif
    inline static const char* models_file = XWIDGETS_MODELS_FILE;

    static const auto schemas = models_to_schemas(read_models(models_file));

    TEST_SUITE("xwidgets")
    {
        TEST_CASE_TEMPLATE_DEFINE("schema", Widget, all_widgets)
        {
            validate_schema(schemas.at(model_name<Widget>()), serialize<Widget>());
        }

        TEST_CASE_TEMPLATE_APPLY(all_widgets, AllWidgets);
        TEST_CASE_TEMPLATE_APPLY(all_widgets, AllStyles);
    }

    /***************************************
     *  Implementation of tests utilities  *
     ***************************************/

    nl::json read_models(const char* file)
    {
        std::ifstream fs{file};
        nl::json models;
        fs >> models;
        return models;
    }

    /**
     * Map types from the model to valid Json schema types.
     */
    nl::json map_types(nl::json const& j)
    {
        static auto const types = std::map<std::string, std::string>{
            {"bool", "boolean"},
            {"int", "integer"},
            {"float", "number"},
            {"bytes", "string"},
            {"reference", "string"},
        };
        auto types_contains = [](auto const& key) -> bool
        {
            return types.find(key) != types.end();
        };

        if (j.is_string())
        {
            if (types_contains(j))
            {
                return types.at(j);
            }
            else
            {
                return j;
            }
        }
        else if (j.is_array())
        {
            nl::json out = nl::json::array();
            std::transform(j.begin(), j.end(), std::back_inserter(out), &map_types);
            return out;
        }
        throw std::invalid_argument(R"(Attribute "type" must be a string or array of string, got )" + j.dump());
    }

    nl::json properties_schema(nl::json p)
    {
        p["type"] = map_types(p["type"]);

        if (p["default"].is_null())
        {
            // The default can be `null` without the type allowing it.
            if (!p["type"].is_array())
            {
                p["type"] = nl::json::array({p["type"]});
            }
            p["type"].push_back("null");
            // The default can be `null` without it being in the `enum`.
            if (p.contains("enum"))
            {
                assert(p["enum"].is_array());
                p["enum"].push_back(nullptr);
            }
        }
        return p;
    }

    /**
     * Heuristics to transform the models file into something of a Json schema.
     */
    nl::json model_to_schema(nl::json const& model)
    {
        static auto constexpr blacklist = std::array{
            "style",
            "tabbable",
            "tooltip",
        };
        auto blacklist_contains = [](auto const& key) -> bool
        {
            return std::find(blacklist.begin(), blacklist.end(), key) != blacklist.end();
        };

        auto required = nl::json::array();
        auto properties = nl::json::object();

        for (auto const& attr : model["attributes"])
        {
            std::string name = attr["name"];
            if (!blacklist_contains(name))
            {
                required.push_back(name);
                properties[name] = properties_schema(attr);
            }
        }

        nl::json schema = nl::json::object({{"type", "object"}});
        schema["required"] = std::move(required);
        schema["properties"] = std::move(properties);
        return schema;
    }

    std::map<std::string, nl::json> models_to_schemas(nl::json const& models)
    {
        std::map<std::string, nl::json> out{};
        for (auto const& mod : models)
        {
            out[mod["model"]["name"]] = model_to_schema(mod);
        }
        return out;
    }

    /**
     * Validate a schema.
     *
     * If the same schema is reused multiple times, it is more peformant to build and store
     * a ``json_validator``.
     */
    void validate_schema(nl::json const& schema, nl::json const& obj)
    {
        nl::json_schema::json_validator validator;

        try
        {
            validator.set_root_schema(schema);
        }
        catch (std::exception const& e)
        {
            throw std::runtime_error("Invalid schema:\n" + schema.dump() + "\nerror is:\n" + e.what());
        }

        try
        {
            validator.validate(obj);
        }
        catch (std::exception const& e)
        {
            throw std::runtime_error(
                "Failed to validate schema:\n" + schema.dump() + "\nwith object:\n" + obj.dump()
                + "\nerror is:\n" + e.what()
            );
        }
    }

    template <typename Widget>
    Widget make_widget()
    {
        return {};
    }

    template <>
    link make_widget<link>()
    {
        return {checkbox{}, "value", checkbox{}, "value"};
    }

    template <>
    directional_link make_widget<directional_link>()
    {
        return {checkbox{}, "value", checkbox{}, "value"};
    }

    template <typename Widget>
    nl::json serialize()
    {
        Widget w = make_widget<Widget>();
        nl::json state;
        xeus::buffer_sequence buffers;
        w.serialize_state(state, buffers);
        return state;
    }

    template <typename Widget>
    std::string model_name()
    {
        if (auto name = make_widget<Widget>()._model_name(); name.has_value())
        {
            return std::move(name).value();
        }
        throw std::invalid_argument("Widget does not have a model name");
    }

}
