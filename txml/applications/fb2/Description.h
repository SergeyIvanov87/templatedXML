#ifndef FB2_DESCRIPTION_H
#define FB2_DESCRIPTION_H
#include "XMLNode.h"
#include "XMLSerializable.h"

class TitleInfo;
class DocumentInfo;
class PublishInfo;
class Description : public XMLNode<Description, TitleInfo, DocumentInfo, PublishInfo>,
                    public XMLSerializable<Description>
{
public:
    using base = XMLNode<Description, TitleInfo, DocumentInfo, PublishInfo>;

    static constexpr const char *class_name()
    {
        return "description";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_DESCRIPTION_H
