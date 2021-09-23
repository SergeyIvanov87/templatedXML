#ifndef XDXF_TO_SCHEMA_SERIALIZER_HPP
#define TO_FB2_SERIALIZER_HPP

#include <txml/include/utils/SchemaSerializer.hpp>

#include <txml/applications/xdxf/XDXFArticle.h>
#include <txml/applications/xdxf/KeyPhrase.h>
#include <txml/applications/xdxf/Comment.h>
#include <txml/applications/xdxf/KeyPhrase.h>
#include <txml/applications/xdxf/TextElement.h>

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
    void serialize_impl(const XDXFArticle*, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", XDXFArticle::class_name());

        out << "article {\n";
        XDXFArticle::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_impl(const KeyPhrase*, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", KeyPhrase::class_name());
        out << "key {\n";
        KeyPhrase::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_impl(const Comment*, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Comment::class_name());
        out << "comment : \"string\",\n";
    }

    template<class Tracer>
    void serialize_impl(const Transcription*, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Transcription::class_name());
        out << "transcription {\n";
        Transcription::schema_serialize_elements(*this, tracer);
        out << "},\n";
    }

    template<class Tracer>
    void serialize_impl(const TextElement*, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", TextElement::class_name());
        out << "text : \"string\"\n";
    }

    Stream &out;
};
} // namespace xdxf
#endif //TO_FB2_SERIALIZER_HPP
