#ifndef FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
#define FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP

#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
using namespace json;
template<class Parent>
TXML_DECLARE_SCHEMA_F_SERIALIZER_TEMPLATED_CLASS(ToJSONSchema_1, Parent, SchemaToJSON,
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
    TXML_SCHEMA_SERIALIZER_OBJECT

};

template<class Parent>
TXML_DECLARE_SCHEMA_F_SERIALIZER_TEMPLATED_CLASS(ToJSONSchema_2, Parent, SchemaToJSON,
                                                            FB2TextElement)
{
    TXML_SCHEMA_SERIALIZER_OBJECT

    using json = nlohmann::json;
    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::LeafTag&& t, Tracer &tracer)
    {
        base_t::template serialize_schema_tag_impl<SerializedItem>(t, tracer);

        // REPACK example
        // Add 'properties' object before unfold every Node/Container members
        // So all Node member become members of 'property' and 'property' itself is a member of Node
        json cur_json_element = json::object({{"properties",
                                               this->json_object_stack_helper->top()[SerializedItem::class_name()]}});
        this->json_object_stack_helper->pop();
        this->json_object_stack_helper->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    }

};

struct ToInjectedSchema : public txml::Dispatcher<ToJSONSchema_1<ToInjectedSchema>, ToJSONSchema_2<ToInjectedSchema>>
{
    using base_t = txml::Dispatcher<ToJSONSchema_1<ToInjectedSchema>, ToJSONSchema_2<ToInjectedSchema>>;
    using json = nlohmann::json;
    ToInjectedSchema(std::shared_ptr<std::stack<json>> shared_object_stack =
                                     std::shared_ptr<std::stack<json>>(new std::stack<json>)) :
        base_t(shared_object_stack)
    {
    }

    using ToJSONSchema_1<ToInjectedSchema>::serialize_schema_impl;
    using ToJSONSchema_2<ToInjectedSchema>::serialize_schema_tag_impl;

};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_INJECTION_HPP
