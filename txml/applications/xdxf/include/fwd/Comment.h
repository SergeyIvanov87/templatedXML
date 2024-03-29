#ifndef COMMENT_H
#define COMMENT_H

#include <ostream>
#include <string>

#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace xdxf
{
class Comment : public txml::XMLNodeLeaf<Comment, std::string>,
                public txml::XMLSerializable<Comment>
{
public:
    using base = txml::XMLNodeLeaf<Comment, std::string>;
    using value_t = typename base::value_t;

    static constexpr std::string_view class_name()
    {
        return "!--";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Text;
    };

    Comment(std::string&& str);
    ~Comment() = default;

    template<class Tracer = txml::EmptyTracer>
    static std::optional<Comment> create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;
};
} // namespace xdxf
#endif //COMMENT_H
