#ifndef FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
#define FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP

#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
using namespace json;
template<class ParentAggregator>
TXML_PREPARE_SCHEMA_SERIALIZER_DISPATCHABLE_CLASS(ToJSONSchema_1, ParentAggregator, SchemaToJSON,
                                                        fb2::FictionBook, fb2::Description, fb2::Body, fb2::Binary,
                                                        fb2::TitleInfo, fb2::DocumentInfo, fb2::PublishInfo,
                                                        fb2::BookTitle, fb2::Author, fb2::Publisher, fb2::ISBN,
                                                        fb2::FirstName, fb2::MiddleName, fb2::LastName, fb2::NickName,
                                                        fb2::Section,
                                                        fb2::Paragraph,
                                                        /*fb2::FB2TextElement, */fb2::Empty)
{
    TXML_SCHEMA_SERIALIZER_DISPATCHABLE_OBJECT

};

template<class ParentAggregator>
TXML_PREPARE_SCHEMA_SERIALIZER_DISPATCHABLE_CLASS(ToJSONSchema_2, ParentAggregator, SchemaToJSON,
                                                            FB2TextElement)
{
    TXML_SCHEMA_SERIALIZER_DISPATCHABLE_OBJECT

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::LeafTag&& t, Tracer &tracer)
    {
        base_t::template serialize_schema_tag_impl<SerializedItem>(t, tracer);

        // REPACK example
        // Add 'properties' object before unfold every Node/Container members
        // So all Node member become members of 'property' and 'property' itself is a member of Node
        auto cur_json_element = base_t::json_core_t::object({{"properties",
                                                             this->get_shared_mediator_object()->top()[SerializedItem::class_name().data()]}});
        this->get_shared_mediator_object()->pop();
        this->get_shared_mediator_object()->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    }

};

TXML_DECLARE_SCHEMA_SERIALIZER_AGGREGATOR_CLASS(ToInjectedSchema, ToJSONSchema_1<ToInjectedSchema>, ToJSONSchema_2<ToInjectedSchema>)
{
    TXML_SCHEMA_SERIALIZER_AGGREGATOR_OBJECT
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
