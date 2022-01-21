#ifndef DOC_INFO_AUTHOR_H
#define DOC_INFO_AUTHOR_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class FirstName;
class MiddleName;
class LastName;
class NickName;
class Author : public txml::XMLNode<Author, FirstName, MiddleName, LastName, NickName>
{
public:
    using base = txml::XMLNode<Author, FirstName, MiddleName, LastName, NickName>;

    static constexpr std::string_view class_name()
    {
        return "author";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //DOC_INFO_AUTHOR_H
