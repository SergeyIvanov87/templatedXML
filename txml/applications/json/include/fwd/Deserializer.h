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
    using core_t = DeserializerCore;
    using json_core_t = core_t::json_core_t;
    using in_stream_core_t = json_core_t;
    using ctor_arg_t = core_t::ctor_arg_t;


    FromJSON(in_stream_core_t &obj, ctor_arg_t = core_t::default_ctor_arg());

    static constexpr std::string_view class_name() { return Impl::name(); }

    // default deserialization routine
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_impl(txml::details::SchemaDTag<DeserializedItem>, Tracer tracer);

protected:

    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::ArrayTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::ContainerTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::LeafTag&, Tracer &tracer);
    template<class DeserializedItem, class Tracer>
    std::optional<DeserializedItem> deserialize_tag_impl(const txml::NoDataTag&, Tracer &tracer);

    template<class NodeType, class Tracer>
    static bool check_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                 json_core_t::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    static bool check_array_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                       json_core_t::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    static bool check_leaf_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                      json_core_t::value_t expected_type, Tracer tracer);
    template<class NodeType, class Tracer>
    static bool check_leaf_no_data_node_param(json_core_t::iterator& cur_it, const json_core_t::iterator& cur_end_it,
                                              Tracer tracer);

    template<class NodeType, class Tracer>
    std::optional<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count);
private:
    static constexpr std::string_view name() { return "FromJSON"; }
};
} // namespace json
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
