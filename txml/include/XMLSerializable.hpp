#ifndef XDXF_PUBLISHING_HPP
#define XDXF_PUBLISHING_HPP

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/utils.h>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os)
{
    return os;
}

template<class Value>
template<class Tracer>
void XMLSerializable<Value>::serialize(std::ostream& out, Tracer tracer) const
{
    tracer.trace("Publish '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    static_cast<const Value*>(this)->serialize_impl(out, tracer);
}




template<class Value>
template<class Formatter, class Tracer>
void XMLFormatSerializable<Value>::format_serialize(Formatter& out, Tracer tracer) const
{
    tracer.trace("Format Publish '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    static_cast<const Value*>(this)->format_serialize_impl(out, tracer);
}


template<class Value>
template<class Formatter, class Tracer>
void XMLSchemaSerializable<Value>::schema_serialize(Formatter& out, Tracer tracer)
{
    tracer.trace("Schema Publish '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    Value::schema_serialize_impl(out, tracer);
}
} // namespace txml
#endif //XDXF_PUBLISHING_HPP
