#ifndef FB2_TO_SCHEMA_SERIALIZER_HPP
#define FB2_TO_SCHEMA_SERIALIZER_HPP

#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{
template<class Stream>
struct ToCustomSchema : public txml::SchemaSerializerBase<ToCustomSchema<Stream>, txml::SkipUnscopedElement,
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
                                                        Binary>
{
    ToCustomSchema(Stream &stream) :
        out(stream)
    {
    }


    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<FictionBook>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", FictionBook::class_name());

        out << "fiction_book {\n";
        FictionBook::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Description>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Description::class_name());
        out << "description {\n";
        Description::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<TitleInfo>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", TitleInfo::class_name());
        out << "title_info {\n";
        TitleInfo::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<BookTitle>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", BookTitle::class_name());
        out << "book_title {\n";
        BookTitle::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<FB2TextElement>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", FB2TextElement::class_name());
        out << "text : \"string\"\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<DocumentInfo>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", DocumentInfo::class_name());
        out << "document_info {\n";
        DocumentInfo::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Empty>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Empty::class_name());
        out << "empty : \"string\"\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<PublishInfo>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", PublishInfo::class_name());
        out << "publish_info {\n";
        PublishInfo::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Body>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Body::class_name());
        out << "body {\n";
        out << "[\n";
        Body::make_schema_serialize(*this, tracer);
        out << "],\n";
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Section>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Section::class_name());
        out << "section {\n";
        out << "[\n";
        Section::make_schema_serialize(*this, tracer);
        out << "],\n";
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Paragraph>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Paragraph::class_name());
        out << "paragraph {\n";
        Paragraph::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Binary>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Binary::class_name());
        out << "binary {\n";
        Binary::make_schema_serialize(*this, tracer);
        out << "},\n";
    }

    Stream &out;
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
