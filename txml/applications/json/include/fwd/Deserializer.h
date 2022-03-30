#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/applications/json/include/fwd/DeserializerCore.h>
#include <txml/include/engine/fwd/FormatDeserializerBase.h>

namespace json
{

template<class Impl, class ...DeserializedItems>
struct FromJSON : public virtual DeserializerCore,
                  public txml::FormatDeserializerBase<Impl, txml::StaticCheckUnscopedElement,
                                                      DeserializedItems...>
{
    using json = nlohmann::json;
    FromJSON(json &obj, std::shared_ptr<std::stack<range_iterator>> shared_iterators_stack =
                                        std::shared_ptr<std::stack<range_iterator>>(new std::stack<range_iterator>));

    // default deserialization routine
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer);

protected:
    json &in;

    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::shared_ptr<DeserializedItem> deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer);

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
    static bool check_leaf_no_data_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                              Tracer tracer);

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count);
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
