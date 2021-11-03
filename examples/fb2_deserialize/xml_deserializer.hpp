#ifndef XML_TO_FB2_DESERIALIZER_HPP
#define XML_TO_FB2_DESERIALIZER_HPP

#include <txml/applications/xml/xml.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
#define DESERIALIZED_TYPES  FictionBook,                                                            \
                                        Description,                                                \
                                                TitleInfo,                                          \
                                                    BookTitle,                                      \
                                                        FB2TextElement,                             \
                                                DocumentInfo,                                       \
                                                    Empty,                                          \
                                                PublishInfo,                                        \
                                                    /*Empty,*/                                      \
                                                Body,                                               \
                                                    Section,                                        \
                                                        Paragraph,                                  \
                                                            /*FB2TextElement,*/                     \
                                                Binary


struct Fb2FromXML : public xml::FromXML<Fb2FromXML,  DESERIALIZED_TYPES>
{
    using xml::FromXML<Fb2FromXML, DESERIALIZED_TYPES>::deserialize_impl;

    template<class Tracer>
    std::shared_ptr<FictionBook> deserialize_impl(txml::details::SchemaDTag<FictionBook>, Tracer tracer)
    {
        if (!in.read() || !check_node_param<FictionBook> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<FictionBook>(tracer);
    }
};

#undef DESERIALIZED_TYPES
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
