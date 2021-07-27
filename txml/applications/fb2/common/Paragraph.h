#ifndef FB2_PARAGRAPH_H
#define FB2_PARAGRAPH_H

#include "XMLNode.h"
#include "XMLSerializable.h"

class FB2TextElement;
class Paragraph : public XMLNode<Paragraph, FB2TextElement>,
                  public XMLSerializable<Paragraph>
{
public:
    using base = XMLNode<Paragraph, FB2TextElement>;
    using value_t = std::string;

    static constexpr const char* class_name()
    {
        return "p";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    };

    const char *name() const noexcept override;
    const value_t &getValue() const;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};

#endif //FB2_PARAGRAPH_H
