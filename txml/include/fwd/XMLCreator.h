#ifndef XML_CREATOR_H
#define XML_CREATOR_H

#include <cassert>
#include <memory>
#include <string>

#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
struct XMLCreator
{
    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_create(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, TextReaderWrapper &reader, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XML_CREATOR_H
