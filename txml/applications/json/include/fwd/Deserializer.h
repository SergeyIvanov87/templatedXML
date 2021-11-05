#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/include/engine/fwd/FormatDeserializerBase.h>

namespace json
{

template<class Impl, class ...DeserializedItems>
struct FromJSON : public txml::FormatDeserializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                      DeserializedItems...>
{
    using json = nlohmann::json;
    FromJSON(json &obj);

    // default deserialization routine
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer);

protected:
    json &in;

    using begin_iterator_t = json::iterator;
    using end_iterator_t = json::iterator;
    using range_iterator = std::pair<begin_iterator_t, end_iterator_t>;
    std::stack<range_iterator> iterators_stack;

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer);

    template<class NodeType, class Tracer>
    static bool check_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                 json::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    static bool check_array_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                       json::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    static bool check_leaf_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                      json::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count);
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
