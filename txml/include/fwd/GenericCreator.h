#ifndef GENERIC_CREATOR_H
#define GENERIC_CREATOR_H

#include <cassert>
#include <optional>
#include <string>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
struct GenericCreator
{
    template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::optional<Value> try_create(DataSource &source, Tracer tracer = Tracer());

    template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::optional<Value> try_fill(std::optional<Value> to_fill, DataSource &source, Tracer tracer = Tracer());
};
} // namespace txml
#endif //GENERIC_CREATOR_H
