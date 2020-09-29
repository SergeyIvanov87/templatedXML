#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include <ostream>

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



#include "XMLNodeLeaf.h"
#include "XMLSerializable.h"

class TextElement : public XMLNodeLeaf<std::string>,
                    public XMLSerializable<TextElement>,
                    public XMLFormatSerializable<TextElement>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "#text";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Text;
    };

    TextElement(std::string&& str);
    ~TextElement() = default;

    const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<TextElement> create_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer);

    /*template<class Tracer = EmptyTracer>
    fill_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer);*/

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
