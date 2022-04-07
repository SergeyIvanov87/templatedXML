#ifndef JSON_TO_FB2_DESERIALIZER_INJECTION_HPP
#define JSON_TO_FB2_DESERIALIZER_INJECTION_HPP

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
using namespace json;
template<class ParentAggregator>
TXML_PREPARE_DESERIALIZER_DISPATCHABLE_CLASS(Fb2FromJSON_1, ParentAggregator, FromJSON,
                                                        fb2::FictionBook, fb2::Description, fb2::Body, fb2::Binary,
                                                        fb2::TitleInfo, fb2::DocumentInfo, fb2::PublishInfo,
                                                        fb2::BookTitle, fb2::Author, fb2::Publisher, fb2::ISBN,
                                                        fb2::FirstName, fb2::MiddleName, fb2::LastName, fb2::NickName,
                                                        fb2::Section,
                                                        fb2::Paragraph,
                                                        /*fb2::FB2TextElement, */fb2::Empty)
{
    TXML_DESERIALIZER_DISPATCHABLE_OBJECT

    template<class Tracer>
    std::shared_ptr<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        auto mediator = this->get_shared_mediator_object();
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

template<class ParentAggregator>
TXML_PREPARE_DESERIALIZER_DISPATCHABLE_CLASS(Fb2FromJSON_2, ParentAggregator, FromJSON,
                                                            FB2TextElement)
{
    TXML_DESERIALIZER_DISPATCHABLE_OBJECT

    template<class Item, class Tracer>
    std::shared_ptr<Item> deserialize_tag_impl(txml::LeafTag&& t, Tracer &tracer)
    {
        auto deserializer_ptr = base_t::template deserialize_tag_impl<Item>(t, tracer);
        return deserializer_ptr;
    }

};

TXML_DECLARE_DESERIALIZER_AGGREGATOR_CLASS(ToInjectedDeserializer, Fb2FromJSON_1<ToInjectedDeserializer>, Fb2FromJSON_2<ToInjectedDeserializer>)
{
    TXML_DESERIALIZER_AGGREGATOR_OBJECT

    // Allocate shared object for all intermediate calculations
    // because each dispatchable serializer must put its own serialized result into shared place
    // to keep final output consistent
    ToInjectedDeserializer(nlohmann::json &obj, std::shared_ptr<std::stack<json::DeserializerCore::range_iterator>> external_iterators_stack =
                           std::shared_ptr<std::stack<json::DeserializerCore::range_iterator>>(new std::stack<json::DeserializerCore::range_iterator>)) :
        base_t(obj, external_iterators_stack)
    {
    }
};
} // namespace fb2
#endif //JSON_TO_FB2_DESERIALIZER_INJECTION_HPP
