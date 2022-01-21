#ifndef FICTION_BOOK_H
#define FICTION_BOOK_H

#include <txml/include/fwd/XMLNode.h>

namespace fb2
{
class Description;
class Body;
class Binary;
class FictionBook : public txml::XMLNode<FictionBook, Description, Body, Binary>
{
public:
    using base = txml::XMLNode<FictionBook, Description, Body, Binary>;

    static constexpr std::string_view class_name()
    {
        return "FictionBook";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }
};
} // namespace fb2
#endif //FICTION_BOOK_H
