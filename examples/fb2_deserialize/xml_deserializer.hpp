#ifndef XML_TO_FB2_DESERIALIZER_HPP
#define XML_TO_FB2_DESERIALIZER_HPP

#include <txml/txml_fwd.h>
#include <txml/applications/xml/xml.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
using namespace xml;
TXML_DECLARE_DESERIALIZER_CLASS(Fb2FromXML, FromXML,
                                FictionBook,
                                        Description,
                                                TitleInfo,
                                                    BookTitle,
                                                        FB2TextElement,
                                                DocumentInfo,
                                                    Empty,
                                                PublishInfo,
                                                    /*Empty,*/
                                                Body,
                                                    Section,
                                                        Paragraph,
                                                            /*FB2TextElement,*/
                                                Binary)
{
    TXML_DESERIALIZER_OBJECT

    template<class Tracer>
    std::shared_ptr<FictionBook> deserialize_impl(txml::details::SchemaDTag<FictionBook>, Tracer tracer)
    {
        if (!in.read() || !check_node_param<FictionBook> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<FictionBook>(tracer);
    }
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
