#ifndef XDXF_CREATABLE_H
#define XDXF_CREATABLE_H

#include <memory>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
struct TextReaderWrapper;

template<class Value>
struct XMLProducible
{
    template<class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = txml::EmptyTracer>
    void fill_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);
};
} // namespace txml
#endif //XDXF_CREATABLE_H
