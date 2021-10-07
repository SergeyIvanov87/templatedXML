#ifndef XDXF_PRODUCIBLE_H
#define XDXF_PRODUCIBLE_H

#include <memory>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
struct TextReaderWrapper;

template<class Value>
struct XMLProducible
{
    template<class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> create_impl(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);
};
} // namespace txml
#endif //XDXF_PRODUCIBLE_H
