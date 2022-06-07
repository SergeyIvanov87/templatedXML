#ifndef TO_FB2_SERIALIZER_HPP
#define TO_FB2_SERIALIZER_HPP

#include <txml/include/engine/FormatSerializerBase.hpp>

#include <txml/applications/xdxf/xdxf.hpp>

#include <txml/applications/fb2/fb2.hpp>

namespace xdxf
{
template<class Stream>
struct ToFB2 : public txml::FormatSerializerBase<ToFB2<Stream>, txml::StaticCheckUnscopedElement,
                                                 XDXFArticle, KeyPhrase, Comment, Transcription, TextElement>
{
    ToFB2(Stream &stream) :
        out(stream)
    {
    }


    template<class Tracer>
    void serialize_impl(const XDXFArticle& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", XDXFArticle::class_name());

        out << "<" << fb2::Section::class_name() << ">\n";
        val.format_serialize_elements(*this, tracer);
        out << "</" << fb2::Section::class_name() << ">\n";
    }

    template<class Tracer>
    void serialize_impl(const KeyPhrase& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", KeyPhrase::class_name());
        out << "<title>";
        val.format_serialize_elements(*this, tracer);
        out << "</title>\n";
        out << "<empty-line/>\n";
    }

    template<class Tracer>
    void serialize_impl(const Comment& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Comment::class_name());
        out << "<" << fb2::Section::class_name() << ">\n";
        out << "<title>";

        out << "<p><emphasis>";
        out << "used: " << val.value() << " times";
        out << "</emphasis></p>";

        out << "</title>\n";
        out << "</" << fb2::Section::class_name() << ">\n";
    }

    template<class Tracer>
    void serialize_impl(const Transcription& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Transcription::class_name());
        out << "<empty-line/>\n";
        out << "<" << fb2::Section::class_name() << ">\n";
        out << "<title>";

        val.format_serialize_elements(*this, tracer);

        out << "</title>\n";
        out << "</" << fb2::Section::class_name() << ">\n";
    }

    template<class Tracer>
    void serialize_impl(const TextElement& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", TextElement::class_name());
        out << "<" << fb2::Paragraph::class_name() << ">";

        //each \n or \r is on new paragraph
        std::stringstream ss;
        val.serialize(ss, tracer);
        const std::string& text = ss.str();
        std::string::size_type start_paragraph_pos = 0, end_paragraph_pos = text.size();
        while((end_paragraph_pos = text.find_first_of("\n\r", start_paragraph_pos)) != std::string::npos)
        {
            out.write(text.data() + start_paragraph_pos, end_paragraph_pos - start_paragraph_pos);
            out << "</" << fb2::Paragraph::class_name() << ">\n";

            out << "<empty-line/>\n";

            start_paragraph_pos = text.find_first_not_of("\n\r", end_paragraph_pos + 1);
            if (start_paragraph_pos == std::string::npos)//< text.size())
            {
                break;
            }

            out << "<" << fb2::Paragraph::class_name() << ">";
        }

        if( start_paragraph_pos != std::string::npos)
        {
            if (end_paragraph_pos == std::string::npos)
            {
                end_paragraph_pos = text.size();
            }
            out.write(text.data() + start_paragraph_pos, end_paragraph_pos - start_paragraph_pos);
        }
        out << "</" << fb2::Paragraph::class_name() << ">\n";
    }

    Stream &out;
};
} // namespace xdxf
#endif //TO_FB2_SERIALIZER_HPP
