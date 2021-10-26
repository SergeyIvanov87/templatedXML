#ifndef TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
#define TXML_APPLICATION_JSON_FWD_DESERIALIZER_H

#include <stack>

#include <nlohmann/json.hpp>

#include <txml/include/utils/Deserializer.hpp>

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

    static const char* json_type_to_cstring(json::value_t type)
    {
        switch(type)
        {
            case json::value_t::null:
                return "'null'";
            case json::value_t::boolean:
                return "'boolean'";
            case json::value_t::string:
                return "'string'";
            case json::value_t::number_integer:
                return "'number (integer)'";
            case json::value_t::number_unsigned:
                return "'number (unsigned integer)'";
            case json::value_t::number_float:
                return "'number (floating-point)'";
            case json::value_t::object:
                return "'object'";
            case json::value_t::array:
                return "'array'";
            case json::value_t::discarded:
                return "'discarded'";
            default:
                return "<unknown>";
        }
    }

    template<class NodeType, class Tracer>
    static bool check_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                 json::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    static bool check_array_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                       json::value_t expected_type, Tracer tracer);

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count);
};
}
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
