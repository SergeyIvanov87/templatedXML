#ifndef XDXF_CREATOR_H
#define XDXF_CREATOR_H

#include <cassert>
#include <memory>
#include <string>
#include <engine/TextReaderWrap.hpp>

#include <utils/Tracer.hpp>

struct XMLCreator
{
    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> try_create(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());
};

#endif //XDXF_CREATOR_H
