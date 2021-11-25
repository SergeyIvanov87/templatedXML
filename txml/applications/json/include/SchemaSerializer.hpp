#ifndef TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP
#define TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP

#include <txml/include/engine/SchemaSerializerBase.hpp>
#include <txml/applications/json/include/fwd/SchemaSerializer.h>
#include <txml/applications/json/include/utils.hpp>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...SerializedItems
#define TEMPL_ARGS_DEF     Impl, SerializedItems...

template<TEMPL_ARGS_DECL>
SchemaToJSON<TEMPL_ARGS_DEF>::SchemaToJSON(json &out_obj) :
  out(out_obj)
{
}

template<TEMPL_ARGS_DECL>
SchemaToJSON<TEMPL_ARGS_DEF>::~SchemaToJSON()
{
    txml::EmptyTracer empty;
    finalize(empty);
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::finalize(Tracer tracer)
{
    size_t awaiting_element_count = json_object_stack.size();
    if (awaiting_element_count == 1)
    {
        tracer.trace(__FUNCTION__, " - from single object, chose ",
                     utils::json_type_to_cstring(json::value_t::object), " as result holder");

        json &serialized_element = json_object_stack.top();
        out = json::object();
        out.insert(serialized_element.begin(), serialized_element.end());
        json_object_stack.pop();
    }
    else if (awaiting_element_count > 1)
    {
        tracer.trace(__FUNCTION__, " - from object count: ", awaiting_element_count, ", chose ",
                     utils::json_type_to_cstring(json::value_t::array), " as result holder");

        out = json::array();
        for (size_t i = 0; i < json_object_stack.size(); i++)
        {
            json &serialized_element = json_object_stack.top();
            tracer.trace(__FUNCTION__, " - merge: ", serialized_element.dump(),
                                   ", to: ", out.dump());
            out.insert(out.end(),serialized_element.begin(), serialized_element.end());
            json_object_stack.pop();
        }
    }
    else
    {
        tracer.trace(__FUNCTION__, " - nothing to finalize...");
    }


    string_result.clear();
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_impl(txml::details::SchemaTag<SerializedItem>, Tracer tracer)
{
    static_cast<Impl*>(this)->template serialize_schema_tag_impl<SerializedItem>(typename SerializedItem::tags_t {}, tracer);
}

template<TEMPL_ARGS_DECL>
std::string SchemaToJSON<TEMPL_ARGS_DEF>::dump() const
{
    if (string_result.empty())
    {
        string_result = out.dump();
    }
    return string_result;
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    //TODO
    json cur_json_element = json::array();
    size_t stack_size_before = json_object_stack.size();

    tracer.trace(__FUNCTION__, " - begin 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    SerializedItem::schema_serialize_elements(*this, tracer);

    size_t stack_size_after = json_object_stack.size();
    tracer.trace(__FUNCTION__, " - end 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json &serialized_element = json_object_stack.top();
        cur_json_element.insert(cur_json_element.end(), std::move(serialized_element));
        json_object_stack.pop();
    }

    json_object_stack.push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(__FUNCTION__, " - 'ArrayTag' merged: ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    json cur_json_element = json::object({});
    size_t stack_size_before = json_object_stack.size();


    tracer.trace(__FUNCTION__, " - begin 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    SerializedItem::schema_serialize_elements(*this, tracer);

    size_t stack_size_after = json_object_stack.size();
    tracer.trace(__FUNCTION__, " - end 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json &serialized_element = json_object_stack.top();
        if (serialized_element.type() == nlohmann::json::value_t::array)
        {
            tracer.trace(__FUNCTION__, " - ", SerializedItem::class_name(), "::emplace array");
            cur_json_element.emplace(SerializedItem::class_name(), std::move(serialized_element));
        }
        else
        {
            auto f = serialized_element.begin();
            auto l = serialized_element.end();
            tracer.trace(__FUNCTION__, " - insert objects count: ", std::distance(f, l));
            cur_json_element.insert(f, l);
        }
        json_object_stack.pop();
    }

    json_object_stack.push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(__FUNCTION__, " - 'ContainerTag' merged: ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer)
{
    tracer.trace(__FUNCTION__, " - begin 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", json_object_stack.size());
    json element({{SerializedItem::class_name(),
                   utils::json_type_to_cstring(utils::type_to_json_type<typename SerializedItem::value_t>()) }});
    tracer.trace("'", SerializedItem::class_name(), "' created, value: ", element.dump());
    json_object_stack.push(std::move(element));
    tracer.trace(__FUNCTION__, " - end 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", json_object_stack.size());
}
} // namespace json
#endif // TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP
