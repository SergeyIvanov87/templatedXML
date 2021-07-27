#ifndef FB2_TITLE_INFO_H
#define FB2_TITLE_INFO_H
#include "XMLNode.h"
#include "XMLSerializable.h"

class BookTitle;
class TitleInfo : public XMLNode<TitleInfo, BookTitle>,
                    public XMLSerializable<TitleInfo>
{
public:
    using base = XMLNode<TitleInfo, BookTitle>;

    static constexpr const char *class_name()
    {
        return "title-info";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;
};
#endif //FB2_TITLE_INFO_H
