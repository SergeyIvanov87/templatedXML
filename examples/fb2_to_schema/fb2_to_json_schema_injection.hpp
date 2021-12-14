#ifndef FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
#define FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP

#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
using namespace json;
template<class ParentAggregator>
TXML_PREPARE_SCHEMA_SERIALIZER_DISPATCHABLE_CLASS(ToJSONSchema_1, ParentAggregator, SchemaToJSON,
                                                        FictionBook,
                                                            Description,
                                                            TitleInfo,
                                                                BookTitle,
                                                                    /*FB2TextElement,*/
                                                            DocumentInfo,
                                                                Empty,
                                                            PublishInfo,
                                                                //Empty,
                                                        Body,
                                                            Section,
                                                                Paragraph,
                                                        Binary)
{
    TXML_SCHEMA_SERIALIZER_DISPATCHABLE_OBJECT

};

template<class ParentAggregator>
TXML_PREPARE_SCHEMA_SERIALIZER_DISPATCHABLE_CLASS(ToJSONSchema_2, ParentAggregator, SchemaToJSON,
                                                            FB2TextElement)
{
    TXML_SCHEMA_SERIALIZER_DISPATCHABLE_OBJECT

    using json = nlohmann::json;
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::LeafTag&& t, Tracer &tracer)
    {
        base_t::template serialize_schema_tag_impl<SerializedItem>(t, tracer);

        // REPACK example
        // Add 'properties' object before unfold every Node/Container members
        // So all Node member become members of 'property' and 'property' itself is a member of Node
        json cur_json_element = json::object({{"properties",
                                               this->get_shared_mediator_object()->top()[SerializedItem::class_name()]}});
        this->get_shared_mediator_object()->pop();
        this->get_shared_mediator_object()->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    }

};

TXML_DECLARE_SCHEMA_SERIALIZER_AGGREGATOR_CLASS(ToInjectedSchema, ToJSONSchema_1<ToInjectedSchema>, ToJSONSchema_2<ToInjectedSchema>)
{
    TXML_SCHEMA_SERIALIZER_AGGREGATOR_OBJECT

    using json = nlohmann::json;

    // Allocate shared object for all intermediate calculations
    // because each dispatchable serializer must put its own serialized result into shared place
    // to keep final output consistent
    ToInjectedSchema(std::shared_ptr<std::stack<json>> shared_object_stack =
                                     std::shared_ptr<std::stack<json>>(new std::stack<json>)) :
        base_t(shared_object_stack)
    {
    }
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
