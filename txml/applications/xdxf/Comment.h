#ifndef COMMENT_H
#define COMMENT_H

#include <ostream>

#include <txml/XMLNodeLeaf.h>
#include <txml/XMLSerializable.h>

class Comment : public XMLNodeLeaf<std::string>,
                public XMLSerializable<Comment>,
                public XMLFormatSerializable<Comment>
{
public:
    using base = XMLNodeLeaf<std::string>;
    using value_t = typename base::value_t;

    static constexpr const char* class_name()
    {
        return "!--";
    }

    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return TextReaderWrapper::NodeType::Text;
    };

    Comment(std::string&& str);
    ~Comment() = default;

    const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Comment> create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;


    template<class Formatter, class Tracer = EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;
};

#endif //COMMENT_H
