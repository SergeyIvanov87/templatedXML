#ifndef TXML_APPLICATION_JSON_SERIALIZER_HPP
#define TXML_APPLICATION_JSON_SERIALIZER_HPP

#include <txml/include/engine/FormatSerializerBase.hpp>
#include <txml/applications/json/include/fwd/Serializer.h>
#include <txml/applications/json/include/SerializerCore.hpp>
#include <txml/applications/json/include/utils.hpp>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...SerializedItems
#define TEMPL_ARGS_DEF     Impl, SerializedItems...

template<TEMPL_ARGS_DECL>
ToJSON<TEMPL_ARGS_DEF>::ToJSON(ctor_arg_t shared_object_stack) :
  core_t(shared_object_stack)
{
}

template<TEMPL_ARGS_DECL>
ToJSON<TEMPL_ARGS_DEF>::~ToJSON() = default;

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_impl(const SerializedItem &val, Tracer tracer)
{
    return static_cast<Impl*>(this)->template serialize_tag_impl(val, typename SerializedItem::tags_t {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::ArrayTag&, Tracer &tracer)
{
    //TODO
    json_core_t cur_json_element = json_core_t::array();
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();

    tracer.trace("begin 'ArrayTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", stack_size_before);

    value.make_format_serialize(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace("end 'ArrayTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json_core_t &serialized_element = mediator->top();
        cur_json_element.insert(cur_json_element.end(), std::move(serialized_element));
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace("'ArrayTag' merged: ", SerializedItem::class_name(),
                 ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag&, Tracer &tracer)
{
    json_core_t cur_json_element = json_core_t::object({});
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();


    tracer.trace("begin 'ContainerTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", stack_size_before);
    value.make_format_serialize(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace("end 'ContainerTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json_core_t &serialized_element = mediator->top();
        if (serialized_element.type() == json_core_t::value_t::array)
        {
            tracer.trace("merge item: ", i, " in '", SerializedItem::class_name(), "' container");
            cur_json_element.emplace(SerializedItem::class_name(), std::move(serialized_element));
        }
        else
        {
            auto f = serialized_element.begin();
            auto l = serialized_element.end();
            tracer.trace("merge objects count: ", std::distance(f, l), " in '", SerializedItem::class_name(), "' container");
            cur_json_element.insert(f, l);
        }
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace("'ContainerTag' merged: ", SerializedItem::class_name(),
                 ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::LeafTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace("begin 'LeafTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", mediator->size());
    json_core_t element({{SerializedItem::class_name(), value.value()}});
    tracer.trace("'", SerializedItem::class_name(), "' created, value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace("end 'LeafTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", mediator->size());
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::NoDataTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace("begin 'NoDataTag' serialization: ", SerializedItem::class_name(),
                 ", stack size: ", mediator->size());
    json_core_t element(SerializedItem::class_name());
    tracer.trace("'", SerializedItem::class_name(), "' created, value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace("end 'NoDataTag' serialization: ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
}
} // namespace json
#endif // TXML_APPLICATION_JSON_SERIALIZER_HPP
