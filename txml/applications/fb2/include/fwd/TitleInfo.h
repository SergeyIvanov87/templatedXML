#ifndef FB2_TITLE_INFO_H
#define FB2_TITLE_INFO_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class BookTitle;
class TitleInfo : public txml::XMLNode<TitleInfo, BookTitle>
{
public:
    using base = txml::XMLNode<TitleInfo, BookTitle>;

    static constexpr const char *class_name()
    {
        return "title-info";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace fb2
#endif //FB2_TITLE_INFO_H
