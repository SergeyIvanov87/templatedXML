#ifndef COMMENT_HPP
#define COMMENT_HPP

#include "XMLNodeLeaf.hpp"
#include "xdxf/Comment.h"
#include "XMLSerializable.hpp"

Comment::Comment(std::string&& str) : base(std::move(str))
{
}

const char *Comment::name() const noexcept
{
    return class_name();
}


template<class Tracer>
void Comment::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Comment::class_name() <<  " word used: " << getValue() << " times -->\n";
}



template<class Formatter, class Tracer = EmptyTracer>
void Comment::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Tracer>
std::shared_ptr<Comment> Comment::create_impl(std::string &name, xmlpp::TextReader &reader, Tracer tracer)
{
    std::shared_ptr<Comment> ret;

    if (name != Comment::class_name())
    {
        throw std::runtime_error(std::string("Expected: ") + Comment::class_name() +
                                 ", got: " + name);
    }

    xmlpp::TextReader::NodeType nodeType = reader.get_node_type();
    if (nodeType != Comment::class_node_type())
    {
        tracer.trace("<skip '", Comment::class_name(), "' for node type: ", to_string(nodeType),
                     ", expected node type: ", to_string(xmlpp::TextReader::NodeType::Text));
        return ret;
    }


    tracer.trace("Open tag '", Comment::class_name(), "'");
    if (reader.has_value())
    {
        const std::string& tmp_value = reader.get_value();
        auto it = tmp_value.begin();
        if (*it == '\r' or *it == '\n')
        {
            ++it;
        }
        ret.reset( new Comment(std::string(it, tmp_value.end())));
        tracer.trace("Value: '", ret->getValue(), "'");
    }

    tracer.trace("Close tag '", Comment::class_name(), "'");
    return ret;
}
#endif //COMMENT_HPP
