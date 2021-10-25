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

    template<class NodeType, class Tracer>
    static bool check_array_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
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

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count)
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
};
}
#endif // TXML_APPLICATION_JSON_FWD_DESERIALIZER_H
