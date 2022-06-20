#ifndef XDXF_PRODUCIBLE_H
#define XDXF_PRODUCIBLE_H

#include <optional>

#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
template<class Value>
struct XMLProducible
{
    template<class Tracer = txml::EmptyTracer>
    static std::optional<Value> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);
};
} // namespace txml
#endif //XDXF_PRODUCIBLE_H
