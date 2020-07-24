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



#include "common/xml/XMLNodeLeaf.h"
#include "common/xml/XMLPublishing.h"

class TextElement : public XMLNodeLeaf<std::string>,
                    public XMLPublishing<TextElement>,
                    public XMLFormattingPublishing<TextElement>
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

    template<class Tracer = Tracer<EmptyTracerImpl>>
    static std::shared_ptr<TextElement> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

    /*template<class Tracer = Tracer<EmptyTracerImpl>>
    fill_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);*/

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
    void format_dump(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //KEY_PHRASE_H
