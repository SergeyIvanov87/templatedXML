#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H

#include <txml/include/fwd/XMLNode.h>
#include <txml/include/fwd/XMLSerializable.h>

class Empty;
class PublishInfo :
                    public XMLNode<PublishInfo, Empty>,
                    public XMLSerializable<PublishInfo>
{
public:
    using base = XMLNode<PublishInfo, Empty>;

    static constexpr const char *class_name()
    {
        return "publish-info";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_PUBLISH_INFO_H
