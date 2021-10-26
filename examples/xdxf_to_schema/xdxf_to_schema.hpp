#ifndef XDXF_TO_SCHEMA_SERIALIZER_HPP
#define XDXF_TO_SCHEMA_SERIALIZER_HPP

#include <txml/include/engine/SchemaSerializerBase.hpp>

#include <txml/applications/xdxf/xdxf.hpp>

namespace xdxf
{
template<class Stream>
struct ToSchema : public txml::SchemaSerializerBase<ToSchema<Stream>, txml::StaticCheckUnscopedElement,
                                                    XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>
{
    ToSchema(Stream &stream) :
        out(stream)
    {
    }


    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<XDXFArticle>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", XDXFArticle::class_name());

        out << "article {\n";
        XDXFArticle::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<KeyPhrase>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", KeyPhrase::class_name());
        out << "key {\n";
        KeyPhrase::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Comment>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Comment::class_name());
        out << "comment : \"string\",\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<Transcription>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Transcription::class_name());
        out << "transcription {\n";
        Transcription::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_schema_impl(txml::details::SchemaTag<TextElement>, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", TextElement::class_name());
        out << "text : \"string\"\n";
    }

    Stream &out;
};
} // namespace xdxf
#endif //XDXF_TO_SCHEMA_SERIALIZER_HPP
