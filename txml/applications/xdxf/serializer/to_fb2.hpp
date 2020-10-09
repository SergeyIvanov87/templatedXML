#ifndef TO_FB2_SERIALIZER_HPP
#define TO_FB2_SERIALIZER_HPP

#include "utils/Serializer.hpp"

#include "xdxf/XDXFArticle.h"
#include "xdxf/KeyPhrase.h"
#include "xdxf/Comment.h"
#include "xdxf/KeyPhrase.h"
#include "xdxf/TextElement.h"

#include "fb2/body/Section.hpp"
//#include "common/fb2/FB2TextElement.hpp"

template<class Stream>
struct ToFB2 : public FormatSerializerBase<ToFB2<Stream>, StaticCheckUnscopedElement, XDXFArticle, KeyPhrase, Comment, /*Transcription, */TextElement>
{
    ToFB2(Stream &stream) :
        out(stream)
    {
    }


    template<class Tracer>
    void map_impl(const XDXFArticle& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", XDXFArticle::class_name());

        out << "<" << Section::class_name() << ">\n";
        val.format_serialize_elements(*this, tracer);
        out << "</" << Section::class_name() << ">\n";
    }

    template<class Tracer>
    void map_impl(const KeyPhrase& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", KeyPhrase::class_name());
        out << "<title>";
        val.format_serialize_elements(*this, tracer);
        out << "</title>\n";
        out << "<empty-line/>\n";
    }

    template<class Tracer>
    void map_impl(const Comment& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Comment::class_name());
        out << "<" << Section::class_name() << ">\n";
        out << "<title>";

        out << "<p><emphasis>";
        out << "used: " << val.getValue() << " times";
        out << "</emphasis></p>";

        out << "</title>\n";
        out << "</" << Section::class_name() << ">\n";
    }

    template<class Tracer>
    void map_impl(const Transcription& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", Transcription::class_name());
        out << "<empty-line/>\n";
        out << "<" << Section::class_name() << ">\n";
        out << "<title>";

        val.format_serialize_elements(*this, tracer);

        out << "</title>\n";
        out << "</" << Section::class_name() << ">\n";
    }

    template<class Tracer>
    void map_impl(const TextElement& val, Tracer tracer)
    {
        tracer.trace(__FUNCTION__, " - ", TextElement::class_name());
        out << "<" << Paragraph::class_name() << ">";

        //each \n or \r is on new paragraph
        std::stringstream ss;
        val.serialize(ss, tracer);
        const std::string& text = ss.str();
        std::string::size_type start_paragraph_pos = 0, end_paragraph_pos = text.size();
        while((end_paragraph_pos = text.find_first_of("\n\r", start_paragraph_pos)) != std::string::npos)
        {
            out.write(text.data() + start_paragraph_pos, end_paragraph_pos - start_paragraph_pos);
            out << "</" << Paragraph::class_name() << ">\n";

            out << "<empty-line/>\n";

            start_paragraph_pos = text.find_first_not_of("\n\r", end_paragraph_pos + 1);
            if (start_paragraph_pos == std::string::npos)//< text.size())
            {
                break;
            }

            out << "<" << Paragraph::class_name() << ">";
        }

        if( start_paragraph_pos != std::string::npos)
        {
            if (end_paragraph_pos == std::string::npos)
            {
                end_paragraph_pos = text.size();
            }
            out.write(text.data() + start_paragraph_pos, end_paragraph_pos - start_paragraph_pos);
        }
        out << "</" << Paragraph::class_name() << ">\n";
    }
/*
    template<class In, int InIndex, class Tracer>
    void map_impl(const In& val, std::integral_constant<int, InIndex> vl, Tracer tracer)
    {
        using mapped_type = std::tuple_element_t<InIndex,
                                    typename out_list_t::impl_t>;

        out << "<" << mapped_type::class_name() << ">";
        val.format_dump(*this, tracer);
        out << "</" << mapped_type::class_name() << ">\n";
    }
    * */
    Stream &out;
};
#endif //TO_FB2_SERIALIZER_HPP
