#ifndef XML_DESERIALIZABLE_H
#define XML_DESERIALIZABLE_H

#include <memory>
#include <ostream>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
template<class Value>
struct XMLFormatDeserializable
{
    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> format_deserialize(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> format_redeserialize(std::shared_ptr<Value>, Formatter& in, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XML_DESERIALIZABLE_H
