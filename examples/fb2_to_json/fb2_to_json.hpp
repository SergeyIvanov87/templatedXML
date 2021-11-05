#ifndef FB2_TO_JSON_SERIALIZER_HPP
#define FB2_TO_JSON_SERIALIZER_HPP

#include <stack>

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace json
{

TXML_DECLARE_SERIALIZER_CLASS(Fb2ToJSON, ToJSON,
                                                    fb2::FictionBook,
                                                        fb2::Description,
                                                            fb2::TitleInfo,
                                                                fb2::BookTitle,
                                                                    fb2::FB2TextElement,
                                                            fb2::DocumentInfo,
                                                                fb2::Empty,
                                                            fb2::PublishInfo,
                                                            fb2::Body,
                                                                fb2::Section,
                                                                    fb2::Paragraph,
                                                                    fb2::Binary)
{
    TXML_SERIALIZER_OBJECT
    using json = nlohmann::json;

};
} // namespace json

#endif // FB2_TO_JSON_SERIALIZER_HPP
