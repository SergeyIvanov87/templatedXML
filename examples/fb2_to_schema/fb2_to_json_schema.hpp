#ifndef FB2_TO_JSON_SCHEMA_SERIALIZER_HPP
#define FB2_TO_JSON_SCHEMA_SERIALIZER_HPP

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
using namespace json;
TXML_DECLARE_SCHEMA_SERIALIZER_CLASS(ToJSONSchema, SchemaToJSON,
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

};

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

    template<class SerializedItem, /*class Tag,*/class Tracer>
    void serialize_schema_tag_impl(txml::ContainerTag&& t, Tracer &tracer)
    {
        base_t::serialize_schema_tag_impl<SerializedItem>(t, tracer);

        // REPACK example
        json cur_json_element = json::object({{"properties", json_object_stack.top()[SerializedItem::class_name()]}});
        json_object_stack.pop();
        json_object_stack.push({{SerializedItem::class_name(), std::move(cur_json_element)}});
    }

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::ArrayTag&& t, Tracer &tracer)
    {
        // NO NEED to REPACK
        base_t::serialize_schema_tag_impl<SerializedItem>(t, tracer);
    }

    template<class SerializedItem, class Tracer>
    void serialize_schema_tag_impl(txml::LeafTag&& t, Tracer &tracer)
    {
        // NO NEED to REPACK
        base_t::serialize_schema_tag_impl<SerializedItem>(t, tracer);
    }
};
}
#endif // FB2_TO_JSON_SCHEMA_SERIALIZER_HPP
