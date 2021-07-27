#ifndef FB2_BODY_H
#define FB2_BODY_H
#include "XMLNode.h"
#include "XMLSerializable.h"
#include "XMLArrayContainerNode.h"

class Section;
class Body : public XMLNode<Body, XMLArrayContainerNode<Section>>,
             public XMLSerializable<Body>
{
public:
    using base = XMLNode<XMLArrayContainerNode<Section>>;

    static constexpr const char *class_name()
    {
        return "body";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_BODY_H
