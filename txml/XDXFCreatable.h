#ifndef XDXF_CREATABLE_H
#define XDXF_CREATABLE_H

#include <memory>

#include <txml/engine/TextReaderWrap.hpp>
#include <txml/utils/Tracer.hpp>

template<class Value>
struct XMLProducible
{
    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Value> create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);
};

#endif //XDXF_CREATABLE_H
