#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP

#include <txml/include/engine/FormatDeserializerBase.hpp>
#include <txml/applications/json/include/fwd/Deserializer.h>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...DeserializedItems
#define TEMPL_ARGS_DEF     Impl, DeserializedItems...

template<TEMPL_ARGS_DECL>
FromJSON<TEMPL_ARGS_DEF>::FromJSON(json &obj) :
  in(obj)
{
    iterators_stack.emplace(in.begin(), in.end());
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
{
    /*auto& [begin_it, end_it] = iterators_stack.top();
    if (!check_node_param<DeserializedItem>(begin_it, end_it, json::value_t::object, tracer))
    {
        return {};
    }

    iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    iterators_stack.pop();
    ++begin_it;

    return ret;*/
    return deserialize_tag_impl<DeserializedItem>(txml::details::SchemaDTag<DeserializedItem> {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    auto& [begin_it, end_it] = iterators_stack.top();
    if (!check_array_node_param<DeserializedItem>(begin_it, end_it, json::value_t::array, tracer))
    {
        return {};
    }

    iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    iterators_stack.pop();
    ++begin_it;

    return ret;
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    auto& [begin_it, end_it] = iterators_stack.top();
    if (!check_node_param<DeserializedItem>(begin_it, end_it, json::value_t::object, tracer))
    {
        return {};
    }

    iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    iterators_stack.pop();
    ++begin_it;

    return ret;
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::shared_ptr<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer)
{
    auto& [begin_it, end_it] = iterators_stack.top();
    if (!check_array_node_param<DeserializedItem>(begin_it, end_it,
                                                  type_to_json_type<typename DeserializedItem::value_t>(),
                                                  tracer))
    {
        return {};
    }

    return std::make_shared<DeserializedItem>((begin_it++).value().get<typename DeserializedItem::value_t>());
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                 json::value_t expected_type, Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const std::string &key = cur_it.key();
    const auto& value = cur_it.value();

    tracer.trace("Found '", key, "', value type: ", json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != expected_type || key != NodeType::class_name())
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(expected_type));
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_array_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                                      json::value_t expected_type, Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const auto& value = cur_it.value();

    tracer.trace("Found: array element, value type: ", json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != expected_type)
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(expected_type));
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
std::shared_ptr<NodeType> FromJSON<TEMPL_ARGS_DEF>::create_deserialized_node(Tracer tracer, size_t available_item_count)
{
    std::shared_ptr<NodeType> ret = std::make_shared<NodeType>();
    tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                 ret.get());

    size_t deserialized_item_count = ret->format_deserialize_elements(*this, tracer);
    while (deserialized_item_count != available_item_count)
    {
        tracer.trace("refill node '", NodeType::class_name(), "' handle: ",
                     ret.get(), " deserialized count: ", deserialized_item_count);
        size_t next_portion_items = ret->format_deserialize_elements(*this, tracer);
        if (deserialized_item_count == next_portion_items)
        {
            break; //nothing more
        }
        deserialized_item_count = next_portion_items;
    }
    return ret;
}


// TODO naive mapping
template<>
constexpr nlohmann::json::value_t type_to_json_type<bool>()
{ return nlohmann::json::value_t::boolean; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<std::string>()
{ return nlohmann::json::value_t::string; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<int>()
{ return nlohmann::json::value_t::number_integer; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<uint>()
{ return nlohmann::json::value_t::number_unsigned; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<float>()
{ return nlohmann::json::value_t::number_float; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<double>()
{ return nlohmann::json::value_t::number_float; }

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
}
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_HPP
