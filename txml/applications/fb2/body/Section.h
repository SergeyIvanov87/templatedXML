#ifndef FB2_SECTION_H
#define FB2_SECTION_H
#include "XMLNode.h"
#include "XMLSerializable.h"
#include "XMLArrayContainerNode.h"

class Paragraph;
class Section : public XMLNode<Section, XMLArrayContainerNode<Paragraph>>,
                public XMLSerializable<Section>
{
public:
    using base = XMLNode<Paragraph>;

    static constexpr const char *class_name()
    {
        return "section";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_SECTION_H
