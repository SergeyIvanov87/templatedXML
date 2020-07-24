#ifndef COMMENT_H
#define COMMENT_H

#include <ostream>

#include "common/xml/XMLNodeLeaf.h"
#include "common/xml/XMLPublishing.h"

class Comment : public XMLNodeLeaf<std::string>,
                public XMLPublishing<Comment>,
                public XMLFormattingPublishing<Comment>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "!--";
    }

    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return xmlpp::TextReader::NodeType::Text;
    };

    Comment(std::string&& str);
    ~Comment() = default;

    const char *name() const noexcept override;

    template<class Tracer = Tracer<EmptyTracerImpl>>
    static std::shared_ptr<Comment> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

    template<class Tracer = Tracer<EmptyTracerImpl>>
    void dump(std::ostream &out, Tracer tracer = Tracer()) const;


    template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
    void format_dump(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //COMMENT_H
