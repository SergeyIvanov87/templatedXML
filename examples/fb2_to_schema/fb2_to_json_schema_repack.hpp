#ifndef FB2_TO_JSON_SCHEMA_SERIALIZER_WITH_REPACK_HPP
#define FB2_TO_JSON_SCHEMA_SERIALIZER_WITH_REPACK_HPP

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
using namespace json;
TXML_DECLARE_SCHEMA_SERIALIZER_CLASS(ToJSONSchemaWithRepack, SchemaToJSON,
                                                    FictionBook,
                                                        Description,
                                                            TitleInfo,
                                                                BookTitle,
                                                                    FB2TextElement,
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

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::ContainerTag&& t, Tracer &tracer)
    {
        base_t::serialize_schema_tag_impl<SerializedItem>(t, tracer);

        // REPACK example
        // Add 'properties' object before unfold every Node/Container members
        // So all Node member become members of 'property' and 'property' itself is a member of Node
        json cur_json_element = json::object({{"properties",
                                               json_object_stack_helper->top()[SerializedItem::class_name()]}});
        json_object_stack_helper->pop();
        json_object_stack_helper->push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    }
};
}
#endif // FB2_TO_JSON_SCHEMA_SERIALIZER_WITH_REPACK_HPP
