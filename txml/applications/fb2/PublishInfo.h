#ifndef FB2_PUBLISH_INFO_H
#define FB2_PUBLISH_INFO_H

#include <txml/XMLNode.h>
#include <txml/XMLSerializable.h>

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
