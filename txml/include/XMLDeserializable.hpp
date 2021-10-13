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

template<class Value>
template<class Formatter, class Tracer>
std::shared_ptr<Value> XMLFormatDeserializable<Value>::format_redeserialize(std::shared_ptr<Value> to_fill,
                                                                          Formatter& in, Tracer tracer)
{
    if (to_fill)
    {
        tracer.trace("fill xml array container with: ", to_fill.get());
        to_fill->format_redeserialize_impl(in, tracer);
    }
    else
    {
        tracer.trace("Incorrect usage for: ", __PRETTY_FUNCTION__);
        assert(false && __PRETTY_FUNCTION__);
    }
    return to_fill;
}
} // namespace txml
#endif //XML_DESERIALIZABLE_HPP
