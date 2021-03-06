#ifndef TEXT_ELEMENT_HPP
#define TEXT_ELEMENT_HPP

#include <regex>
#include "XMLNodeLeaf.hpp"
#include "xdxf/TextElement.h"
#include "XMLSerializable.hpp"

TextElement::TextElement(std::string&& str) : base(std::move(str))
{
}

const char *TextElement::name() const noexcept
{
    return class_name();
}


template<class Tracer>
void TextElement::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    //skip special symbols
    static std::regex e(R"(&\S+;)");

    const std::string& value = getValue();
    // iterate through matches (0) and non-matches (-1)
    std::sregex_token_iterator itr(value.begin(), value.end(), e, {-1, 0});
    std::sregex_token_iterator end;

    for(; itr != end; ++itr)
    {
        std::string s = *itr;
        if(!std::regex_match(s, e))
        {
            s = std::regex_replace(s, std::regex("&"), "&amp;");
            s = std::regex_replace(s, std::regex("<"), "&lt;");
            s = std::regex_replace(s, std::regex(">"), "&gt;");
            s = std::regex_replace(s, std::regex("\""), "&quot;");
            s = std::regex_replace(s, std::regex("'"), "&apos;");
        }
        out << s;

        tracer.trace (__FUNCTION__, " - ", s);
    }
}


template<class Formatter, class Tracer = EmptyTracer>
void TextElement::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Tracer>
std::shared_ptr<TextElement> TextElement::create_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer)
{
    std::shared_ptr<TextElement> ret;

    if (name != TextElement::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + TextElement::class_name() +
                                 ", got: " + name);
    }

    xmlpp::TextReader::NodeType nodeType = reader.get_node_type();
    if (nodeType != TextElement::class_node_type())
    {
        tracer.trace("<skip '", TextElement::class_name(), "' for node type: ", to_string(nodeType),
                     ", expected node type: ", to_string(xmlpp::TextReader::NodeType::Text));
        return ret;
    }


    tracer.trace("Open tag '", TextElement::class_name(), "'");
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret.reset( new TextElement(std::string(it, tmp_value.end())));
        tracer.trace("Value: '", ret->getValue(), "'");
    }

    tracer.trace("Close tag '", TextElement::class_name(), "'");
    return ret;
}

/*
template<class Tracer>
void TextElement::fill_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer)
{
}
*/
#endif //TEXT_ELEMENT_HPP
