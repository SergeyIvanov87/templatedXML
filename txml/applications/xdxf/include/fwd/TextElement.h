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
class TextElement : public txml::XMLNodeLeaf<std::string>,
                    public txml::XMLSerializable<TextElement>,
                    public txml::XMLFormatSerializable<TextElement>,
                    public txml::XMLSchemaSerializable<TextElement>
{
public:
    using base = txml::XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "#text";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    TextElement(std::string&& str);
    ~TextElement() = default;

    const char *name() const noexcept override;

    template<class Tracer = txml::EmptyTracer>
    static std::shared_ptr<TextElement> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

    /*template<class Tracer = txml::EmptyTracer>
    fill_impl(std::string &name, txml::TextReaderWrapper &reader, Tracer tracer);*/

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace xdxf
#endif //KEY_PHRASE_H
