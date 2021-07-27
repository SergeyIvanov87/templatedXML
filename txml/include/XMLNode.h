#ifndef XDXF_VALUEBASE_H
#define XDXF_VALUEBASE_H

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
#include <engine/TextReaderWrap.hpp>

#include <utils/Tracer.hpp>

#include "details/GenericCommandArguments.h"
#include "XMLProducible.h"

template<class Impl, class ...ContainedValues>
struct XMLNode : public std::enable_shared_from_this<XMLNode<Impl, ContainedValues...>>,
                 public XMLProducible<Impl>,
                 public ArgumentContainerBase<ContainedValues...>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;

    virtual const char *name() const noexcept = 0;

    std::shared_ptr<XMLNode<Impl, ContainedValues...>> get_ptr();

    template<class Tracer = EmptyTracer>
    bool initialize(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

    void serialize_impl(std::ostream &out) const;
    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> create(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

protected:
    XMLNode() = default;
    ~XMLNode() = default;
};


#endif //VALUEBASE_VALUE_H
