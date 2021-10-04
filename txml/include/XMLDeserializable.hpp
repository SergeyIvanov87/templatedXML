#ifndef XML_DESERIALIZABLE_HPP
#define XML_DESERIALIZABLE_HPP

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/utils.h>

namespace txml
{
template<class Value>
template<class Formatter, class Tracer>
std::shared_ptr<Value> XMLFormatDeserializable<Value>::format_deserialize(Formatter& in, Tracer tracer)
{
    tracer.trace("Format deserialize '", Value::class_name(), "'", " with node type '",
                 to_string(Value::class_node_type()), "'");

    return Value::format_deserialize_impl(in, tracer);
}
} // namespace txml
#endif //XML_DESERIALIZABLE_HPP
