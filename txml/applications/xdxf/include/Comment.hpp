#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

#include <txml/applications/xdxf/include/fwd/Comment.h>

namespace xdxf
{
inline Comment::Comment(std::string&& str) : base(std::move(str))
{
}

template<class Tracer>
inline void Comment::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Comment::class_name() <<  " word used: " << getValue() << " times -->\n";
}


template<class Tracer>
inline std::shared_ptr<Comment> Comment::create_impl(/*std::string &name, */txml::TextReaderWrapper &reader, Tracer tracer)
{
    std::shared_ptr<Comment> ret;
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
    return ret;
}
} // namespace xdxf
#endif //COMMENT_HPP
