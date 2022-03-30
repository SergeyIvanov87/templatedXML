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
ToJSON<TEMPL_ARGS_DEF>::ToJSON(std::shared_ptr<std::stack<json>> shared_object_stack) :
  SerializerCore(shared_object_stack)
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
    json cur_json_element = json::array();
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();

    tracer.trace(__FUNCTION__, " - begin 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    value.format_serialize_elements(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace(__FUNCTION__, " - end 'ArrayTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json &serialized_element = mediator->top();
        cur_json_element.insert(cur_json_element.end(), std::move(serialized_element));
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(__FUNCTION__, " - 'ArrayTag' merged: ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::ContainerTag&, Tracer &tracer)
{
    json cur_json_element = json::object({});
    auto mediator = get_shared_mediator_object();
    size_t stack_size_before = mediator->size();


    tracer.trace(__FUNCTION__, " - begin 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_before);

    value.format_serialize_elements(* static_cast<Impl*>(this), tracer);

    size_t stack_size_after = mediator->size();
    tracer.trace(__FUNCTION__, " - end 'ContainerTag': ", SerializedItem::class_name(),
                               ", stack size: ", stack_size_after);
    for (size_t i = stack_size_before; i < stack_size_after; i++)
    {
        json &serialized_element = mediator->top();
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
        mediator->pop();
    }

    mediator->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    tracer.trace(__FUNCTION__, " - 'ContainerTag' merged: ", SerializedItem::class_name(),
                               ", from elements count: ", stack_size_after - stack_size_before);
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::LeafTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace(__FUNCTION__, " - begin 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
    json element({{SerializedItem::class_name(), value.getValue()}});
    tracer.trace("'", SerializedItem::class_name(), "' created, value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace(__FUNCTION__, " - end 'LeafTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
}

template<TEMPL_ARGS_DECL>
template<class SerializedItem, class Tracer>
void ToJSON<TEMPL_ARGS_DEF>::serialize_tag_impl(const SerializedItem& value, const txml::NoDataTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    tracer.trace(__FUNCTION__, " - begin 'NoDataTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
    json element(SerializedItem::class_name());
    tracer.trace("'", SerializedItem::class_name(), "' created, value: ", element.dump());
    mediator->push(std::move(element));
    tracer.trace(__FUNCTION__, " - end 'NoDataTag': ", SerializedItem::class_name(),
                               ", stack size: ", mediator->size());
}
} // namespace json
#endif // TXML_APPLICATION_JSON_SERIALIZER_HPP
