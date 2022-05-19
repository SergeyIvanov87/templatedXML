#ifndef XML_DESERIALIZABLE_H
#define XML_DESERIALIZABLE_H

#include <optional>
#include <ostream>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
template<class Value>
struct XMLFormatDeserializable
{
    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Value> format_deserialize(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Value> format_redeserialize(std::optional<Value>, Formatter& in, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XML_DESERIALIZABLE_H
