#ifndef XML_CREATOR_H
#define XML_CREATOR_H

#include <cassert>
#include <memory>
#include <string>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
struct TextReaderWrapper;

struct XMLCreator
{
    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_create(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, TextReaderWrapper &reader, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XML_CREATOR_H
