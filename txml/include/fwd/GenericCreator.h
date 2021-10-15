#ifndef GENERIC_CREATOR_H
#define GENERIC_CREATOR_H

#include <cassert>
#include <memory>
#include <string>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
struct GenericCreator
{
    template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_create(DataSource &source, Tracer tracer = Tracer());

    template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> try_fill(std::shared_ptr<Value> to_fill, DataSource &source, Tracer tracer = Tracer());
};
} // namespace txml
#endif //GENERIC_CREATOR_H
