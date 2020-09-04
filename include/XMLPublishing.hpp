#ifndef XDXF_PUBLISHING_HPP
#define XDXF_PUBLISHING_HPP

#include "XMLPublishing.h"
#include "utils.h"

inline std::ostream& no_sep (std::ostream& os)
{
    return os;
}

template<class Value>
template<class Tracer>
void XMLPublishing<Value>::publish_impl(std::ostream& out, Tracer tracer) const
{
    tracer.trace("Publish '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    static_cast<const Value*>(this)->dump(out, tracer);
}




template<class Value>
template<class Formatter, class Tracer>
void XMLFormattingPublishing<Value>::format_publish_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace("Format Publish '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    static_cast<const Value*>(this)->format_dump(out, tracer);
}

#endif //XDXF_PUBLISHING_HPP
