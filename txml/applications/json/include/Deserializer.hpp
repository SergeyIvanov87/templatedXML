#ifndef TXML_APPLICATION_JSON_DESERIALIZER_HPP
#define TXML_APPLICATION_JSON_DESERIALIZER_HPP

#include <txml/include/engine/FormatDeserializerBase.hpp>
#include <txml/applications/json/include/fwd/Deserializer.h>
#include <txml/applications/json/include/DeserializerCore.hpp>
#include <txml/applications/json/include/utils.hpp>

namespace json
{
#define TEMPL_ARGS_DECL    class Impl, class ...DeserializedItems
#define TEMPL_ARGS_DEF     Impl, DeserializedItems...

template<TEMPL_ARGS_DECL>
FromJSON<TEMPL_ARGS_DEF>::FromJSON(json_core_t &obj, ctor_arg_t shared_iterators_stack) :
  core_t(obj, shared_iterators_stack)
{
    get_shared_mediator_object()->emplace(in.begin(), in.end());
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer)
{
    return static_cast<Impl*>(this)->template deserialize_tag_impl<DeserializedItem>(txml::details::SchemaDTag<DeserializedItem> {}, tracer);
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    auto& [begin_it, end_it] = mediator->top();
    if (!check_array_node_param<DeserializedItem>(begin_it, end_it, json_core_t::value_t::array, tracer))
    {
        return {};
    }

    mediator->emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    mediator->pop();
    ++begin_it;

    return ret;
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer)
{
    auto mediator = get_shared_mediator_object();
    auto& [begin_it, end_it] = mediator->top();
    if (!check_node_param<DeserializedItem>(begin_it, end_it, json_core_t::value_t::object, tracer))
    {
        return {};
    }

    mediator->emplace(begin_it.value().begin(), begin_it.value().end());
    auto ret = create_deserialized_node<DeserializedItem>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
    mediator->pop();
    ++begin_it;

    return ret;
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer)
{

    auto& [begin_it, end_it] = get_shared_mediator_object()->top();
    if (!check_leaf_node_param<DeserializedItem>(begin_it, end_it,
                                                 utils::type_to_json_type<typename DeserializedItem::value_t>(),
                                                 tracer))
    {
        return {};
    }

    return std::make_optional<DeserializedItem>((begin_it++).value().get<typename DeserializedItem::value_t>());
}

template<TEMPL_ARGS_DECL>
template<class DeserializedItem, class Tracer>
std::optional<DeserializedItem> FromJSON<TEMPL_ARGS_DEF>::deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer)
{

    auto& [begin_it, end_it] = get_shared_mediator_object()->top();
    if (!check_leaf_no_data_node_param<DeserializedItem>(begin_it, end_it, tracer))
    {
        return {};
    }

    begin_it++;
    return std::make_shared<DeserializedItem>();
}


template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                 json_core_t::value_t expected_type, Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const std::string &key = cur_it.key();
    const auto& value = cur_it.value();

    tracer.trace("Found '", key, "', value type: ", utils::json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != expected_type || key != NodeType::class_name())
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", utils::json_type_to_cstring(expected_type));
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_array_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                                      json_core_t::value_t expected_type, Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const auto& value = cur_it.value();

    tracer.trace("Found: array element, value type: ", utils::json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != expected_type)
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", utils::json_type_to_cstring(expected_type));
        return false;
    }
    return true;
}


template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_leaf_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                                     json_core_t::value_t expected_type, Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const std::string &key = cur_it.key();
    const auto& value = cur_it.value();

    tracer.trace("Found '", key, "', value type: ", utils::json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != expected_type || key != NodeType::class_name())
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", utils::json_type_to_cstring(expected_type));
        return false;
    }
    return true;
}

template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
bool FromJSON<TEMPL_ARGS_DEF>::check_leaf_no_data_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                                             Tracer tracer)
{
    if (cur_it == cur_end_it)
    {
        tracer.trace("EOF");
        return false;
    }

    const std::string &key = cur_it.key();
    const auto& value = cur_it.value();

    tracer.trace("Found '", key, "', value type: ", utils::json_type_to_cstring(value.type()), ", value:\n", value);
    if (value.type() != json_core_t::value_t::discarded || key != NodeType::class_name())
    {
        tracer.trace("Expected '", NodeType::class_name(), "', type: ", utils::json_type_to_cstring(json_core_t::value_t::discarded));
        return false;
    }
    return true;
}
template<TEMPL_ARGS_DECL>
template<class NodeType, class Tracer>
std::optional<NodeType> FromJSON<TEMPL_ARGS_DEF>::create_deserialized_node(Tracer tracer, size_t available_item_count)
{
    std::optional<NodeType> ret = std::make_optional<NodeType>();
    tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                 ret, ", available subnodes count: ", available_item_count);

    size_t deserialized_item_count = ret->format_deserialize_impl(* static_cast<Impl*>(this), tracer);
    while (deserialized_item_count != available_item_count)
    {
        tracer.trace("refill node '", NodeType::class_name(), "' handle: ",
                     ret, " deserialized count: ", deserialized_item_count);
        size_t next_portion_items = ret->format_deserialize_impl(* static_cast<Impl*>(this), tracer);
        if (deserialized_item_count == next_portion_items)
        {
            auto& [begin_it, end_it] = get_shared_mediator_object()->top();
            if (++begin_it == end_it)
            {
                // TODO process skipped elements, which are not part of model!
                break; //nothing more
            }

            available_item_count--;
        }
        deserialized_item_count = next_portion_items;
    }
    return ret;
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
}
#endif // TXML_APPLICATION_JSON_DESERIALIZER_HPP
