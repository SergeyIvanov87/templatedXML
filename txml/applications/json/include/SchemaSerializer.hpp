#ifndef TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP
#define TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP

#include <txml/include/engine/SchemaSerializerBase.hpp>
#include <txml/applications/json/include/fwd/SchemaSerializer.h>
#include <txml/applications/json/include/SerializerCore.hpp>
#include <txml/applications/json/include/utils.hpp>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...SerializedItems
#define TEMPL_ARGS_DEF     Impl, SerializedItems...

template<TEMPL_ARGS_DECL>
SchemaToJSON<TEMPL_ARGS_DEF>::SchemaToJSON(ctor_arg_t shared_object_stack) :
  core_t(shared_object_stack)
{
}

template<TEMPL_ARGS_DECL>
SchemaToJSON<TEMPL_ARGS_DEF>::~SchemaToJSON() = default;

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_impl(txml::details::SchemaTag<SerializedItem>, Tracer tracer)
{
    static_cast<Impl*>(this)->template serialize_schema_tag_impl<SerializedItem>(typename SerializedItem::tags_t {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    //TODO
    json_core_t cur_json_element = json_core_t::array();
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();

    tracer.trace(class_name(), " - begin ", __FUNCTION__, " - for 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    SerializedItem::make_schema_serialize(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace(class_name(), " - end ", __FUNCTION__, " - for 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json_core_t &serialized_element = mediator->top();
        cur_json_element.insert(cur_json_element.end(), std::move(serialized_element));
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(class_name(), " - finish ", __FUNCTION__, " - merged 'ArrayTag': ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    json_core_t cur_json_element = json_core_t::object({});
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();


    tracer.trace(class_name(), " - begin ", __FUNCTION__, " - for 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    SerializedItem::make_schema_serialize(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace(class_name(), " - end ", __FUNCTION__, " - for 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json_core_t &serialized_element = mediator->top();
        if (serialized_element.type() == json_core_t::value_t::array)
        {
            tracer.trace(class_name(), " - emplace ", __FUNCTION__, " - array for ", SerializedItem::class_name());
            cur_json_element.emplace(SerializedItem::class_name(), std::move(serialized_element));
        }
        else
        {
            auto f = serialized_element.begin();
            auto l = serialized_element.end();
            tracer.trace(class_name(), " - insert ", __FUNCTION__, " - objects count: ", std::distance(f, l));
            cur_json_element.insert(f, l);
        }
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(class_name(), " - finish ", __FUNCTION__, " - merged 'ContainerTag': ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::LeafTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace(class_name(), " - begin ", __FUNCTION__, " - for 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
    json_core_t element({{SerializedItem::class_name(),
                   utils::json_type_to_cstring(utils::type_to_json_type<typename SerializedItem::value_t>()) }});
    tracer.trace(class_name(), " created '", SerializedItem::class_name(), "', value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace(class_name(), " - end ", __FUNCTION__, " - for 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void SchemaToJSON<TEMPL_ARGS_DEF>::serialize_schema_tag_impl(const txml::NoDataTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace(class_name(), " - begin ", __FUNCTION__, " - for 'NoDataTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
    json_core_t element({{SerializedItem::class_name()}});
    tracer.trace(class_name(), " created '", SerializedItem::class_name(), "', value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace(class_name(), " - end ", __FUNCTION__, " - for 'NoDataTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
}
} // namespace json
#endif // TXML_APPLICATION_JSON_SCHEMA_SERIALIZER_HPP
