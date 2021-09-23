#ifndef XDXF_CREATOR_H
#define XDXF_CREATOR_H

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
    static std::shared_ptr<Value> try_create(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XDXF_CREATOR_H
