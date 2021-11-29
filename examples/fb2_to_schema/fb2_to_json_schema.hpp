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
}
#endif // FB2_TO_JSON_SCHEMA_SERIALIZER_HPP
