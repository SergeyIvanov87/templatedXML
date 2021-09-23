#ifndef XDXF_VALUEBASE_H
#define XDXF_VALUEBASE_H

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/utils/Tracer.hpp>
#include <txml/include/details/GenericCommandArguments.h>
#include <txml/include/fwd/XMLProducible.h>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class ...ContainedValues>
struct XMLNode : public std::enable_shared_from_this<XMLNode<Impl, ContainedValues...>>,
                 public XMLProducible<Impl>,
                 public ArgumentContainerBase<ContainedValues...>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;

    virtual const char *name() const noexcept = 0;

    std::shared_ptr<XMLNode<Impl, ContainedValues...>> get_ptr();

    template<class Tracer = txml::EmptyTracer>
    bool initialize(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

    void serialize_impl(std::ostream &out) const;
    template<class Value, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Value> create(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());

protected:
    XMLNode() = default;
    ~XMLNode() = default;
};
} // namespace txml
#endif //VALUEBASE_VALUE_H
