#ifndef FB2_BODY_H
#define FB2_BODY_H
#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLPublishing.h"
#include "XMLArrayContainerNode.h"

class Section;
class Body : public XMLNode<XMLArrayContainerNode<Section>>,
             public XMLProducible<Body>,
             public XMLPublishing<Body>
{
public:
    using base = XMLNode<XMLArrayContainerNode<Section>>;

    static constexpr const char *class_name()
    {
        return "body";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_BODY_H
