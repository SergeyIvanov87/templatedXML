#ifndef JSON_TO_FB2_DESERIALIZER_HPP
#define JSON_TO_FB2_DESERIALIZER_HPP

#include <stack>

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
using namespace json;
TXML_DECLARE_DESERIALIZER_CLASS(Fb2FromJSON, FromJSON, FB2_CLASS_LIST)
{
    TXML_DESERIALIZER_OBJECT
    template<class Tracer>
    std::optional<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        auto mediator = get_shared_mediator_object();
        auto& [begin_it, end_it] = mediator->top();
        if (!check_array_node_param<Paragraph>(begin_it, end_it, base_t::json_core_t::value_t::object, tracer))
        {
            return {};
        }

        mediator->emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Paragraph>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        mediator->pop();
        ++begin_it;
        return ret;
    }
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
