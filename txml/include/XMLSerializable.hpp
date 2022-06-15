#ifndef XMK_SERIALIZABLE_HPP
#define XMK_SERIALIZABLE_HPP

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/utils.h>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os)
{
    return os;
}

template<class Value>
template<class Tracer>
void XMLSerializable<Value>::xml_serialize(std::ostream& out, Tracer tracer) const
{
    tracer.trace("publish '", Value::class_name(), "' (",
                 to_string(Value::class_node_type()), ")");

    static_cast<const Value*>(this)->make_xml_serialize(out, tracer);
}




template<class Value>
template<class Formatter, class Tracer>
void XMLFormatSerializable<Value>::format_serialize(Formatter& out, Tracer tracer) const
{
    tracer.trace("publish '", Value::class_name(), "' (",
                 to_string(Value::class_node_type()), ")");

    static_cast<const Value*>(this)->format_serialize_request(out, tracer);
}


template<class Value>
template<class Formatter, class Tracer>
void XMLSchemaSerializable<Value>::schema_serialize(Formatter& out, Tracer tracer)
{
    tracer.trace("publish '", Value::class_name(), "' (",
                 to_string(Value::class_node_type()), ")");

    Value::schema_serialize_request(out, tracer);
}
} // namespace txml
#endif //XMK_SERIALIZABLE_HPP
