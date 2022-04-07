#ifndef FB2_TO_JSON_SERIALIZER_INJECTION_HPP
#define FB2_TO_JSON_SERIALIZER_INJECTION_HPP

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
using namespace json;
template<class ParentAggregator>
TXML_PREPARE_SERIALIZER_DISPATCHABLE_CLASS(Fb2ToJSON_1, ParentAggregator, ToJSON,
                                                        fb2::FictionBook, fb2::Description, fb2::Body, fb2::Binary,
                                                        fb2::TitleInfo, fb2::DocumentInfo, fb2::PublishInfo,
                                                        fb2::BookTitle, fb2::Author, fb2::Publisher, fb2::ISBN,
                                                        fb2::FirstName, fb2::MiddleName, fb2::LastName, fb2::NickName,
                                                        fb2::Section,
                                                        fb2::Paragraph,
                                                        /*fb2::FB2TextElement, */fb2::Empty)
{
    TXML_SERIALIZER_DISPATCHABLE_OBJECT
};

template<class ParentAggregator>
TXML_PREPARE_SERIALIZER_DISPATCHABLE_CLASS(Fb2ToJSON_2, ParentAggregator, ToJSON,
                                                            FB2TextElement)
{
    TXML_SERIALIZER_DISPATCHABLE_OBJECT

    template<class Item, class Tracer>
    void serialize_tag_impl(const Item& value, const txml::LeafTag& t, Tracer &tracer)
    {
        base_t::template serialize_tag_impl<Item>(value, t, tracer);
    }

};

TXML_DECLARE_SERIALIZER_AGGREGATOR_CLASS(ToInjectedSerializer, Fb2ToJSON_1<ToInjectedSerializer>, Fb2ToJSON_2<ToInjectedSerializer>)
{
    TXML_SERIALIZER_AGGREGATOR_OBJECT

    // Allocate shared object for all intermediate calculations
    // because each dispatchable serializer must put its own serialized result into shared place
    // to keep final output consistent
    ToInjectedSerializer(std::shared_ptr<std::stack<json::SerializerCore::json_core_t>> external_iterators_stack =
                           std::shared_ptr<std::stack<json::SerializerCore::json_core_t>>(new std::stack<json::SerializerCore::json_core_t>)) :
        base_t(external_iterators_stack)
    {
    }
};
} // namespace fb2
#endif //FB2_TO_JSON_SERIALIZER_INJECTION_HPP
