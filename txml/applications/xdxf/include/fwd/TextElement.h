#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include <ostream>
#include <string>

inline std::ostream& bold_on(std::ostream& os)
{
    return os ;//<< "\e[1m";
}

inline std::ostream& bold_off(std::ostream& os)
{
    return os;// << "\e[0m";
}

inline std::ostream& italic_on(std::ostream& os)
{
    return os;// << "\e[3m";
}

inline std::ostream& italic_off(std::ostream& os)
{
    return os;// << "\e[0m";
}



#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace xdxf
{
class TextElement : public txml::XMLNodeLeaf<TextElement, std::string>,
                    public txml::XMLSerializable<TextElement>
{
public:
    using base = txml::XMLNodeLeaf<TextElement, std::string>;
    using value_t = typename base::value_t;

    static constexpr std::string_view class_name()
    {
        return "#text";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    TextElement(std::string&& str);
    TextElement(const std::string& str);
    ~TextElement() = default;

    template<class Tracer = txml::EmptyTracer>
    static std::optional<TextElement> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

    /*template<class Tracer = txml::EmptyTracer>
    fill_impl(std::string &name, txml::TextReaderWrapper &reader, Tracer tracer);*/

    template<class Tracer = txml::EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;
};
} // namespace xdxf
#endif //TEXT_ELEMENT_H
