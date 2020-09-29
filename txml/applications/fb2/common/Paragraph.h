#ifndef FB2_PARAGRAPH_H
#define FB2_PARAGRAPH_H

#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLSerializable.h"

class FB2TextElement;
class Paragraph : public XMLNode<FB2TextElement>,
                  public XMLProducible<Paragraph>,
                  public XMLSerializable<Paragraph>
{
public:
    using base = XMLNode<FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "p";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //FB2_PARAGRAPH_H
