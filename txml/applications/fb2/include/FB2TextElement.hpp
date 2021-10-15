#ifndef FB2_TEXT_ELEMENT_HPP
#define FB2_TEXT_ELEMENT_HPP

#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

#include <txml/applications/fb2/include/fwd/FB2TextElement.h>

namespace fb2
{
FB2TextElement::FB2TextElement(std::string&& str) : base(std::move(str))
{
}

const char *FB2TextElement::name() const noexcept
{
    return class_name();
}


template<class Tracer>
void FB2TextElement::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
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
    }
}

template<class Tracer>
std::shared_ptr<FB2TextElement> FB2TextElement::create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer)
{
    std::shared_ptr<FB2TextElement> ret;
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret.reset( new FB2TextElement(std::string(it, tmp_value.end())));
        tracer.trace("Value: '", ret->getValue(), "'");
    }

    return ret;
}
} // namespace fb2
#endif //FB2_TEXT_ELEMENT_HPP
