#ifndef GENERIC_CREATOR_H
#define GENERIC_CREATOR_H

#include <cassert>
#include <optional>
#include <string>
#include <txml/include/utils/fwd/utils.h>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
template<class Impl, class ...ContainedValues>
struct XMLNode;

struct GenericCreator
{
    /*template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::optional<Value> try_create(DataSource &source, Tracer tracer = Tracer());

    template<class Value, class DataSource, class Tracer = txml::EmptyTracer>
    static std::optional<Value> try_fill(std::optional<Value> to_fill, DataSource &source, Tracer tracer = Tracer());*/
    template<class Value, class ...SpecificContainedValues>
    static std::optional<Value> try_create(SpecificContainedValues &&...args);


    template<class Value, class Value2, class ...SpecificContainedValues, class ...OtherValues>
    static std::optional<Value> try_create(const XMLNode<Value2, SpecificContainedValues...> &node, OtherValues&& ...args);
};
} // namespace txml
#endif //GENERIC_CREATOR_H
