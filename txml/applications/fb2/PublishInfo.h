#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H
#include "XMLNode.h"
#include "XMLProducible.h"
#include "XMLSerializable.h"

class Empty;
class PublishInfo :
                    public XMLNode<Empty>,
                    public XMLProducible<PublishInfo>,
                    public XMLSerializable<PublishInfo>
{
public:
    using base = XMLNode<Empty>;

    static constexpr const char *class_name()
    {
        return "publish-info";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer = Tracer());

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_PUBLISH_INFO_H
