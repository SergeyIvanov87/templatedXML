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

    static constexpr const char *class_name()
    {
        return "FictionBook";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    }

    virtual const char *name() const noexcept override;
};
} // namespace fb2
#endif //FICTION_BOOK_H
