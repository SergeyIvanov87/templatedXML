#ifndef XDXF_VALUEBASE_H
#define XDXF_VALUEBASE_H

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <utils/Tracer.hpp>

#include "details/GenericCommandArguments.h"

template<class ...ContainedValues>
struct XMLNode : public std::enable_shared_from_this<XMLNode<ContainedValues...>>,
                 public ArgumentContainerBase<ContainedValues...>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;

    virtual const char *name() const noexcept = 0;

    std::shared_ptr<XMLNode<ContainedValues...>> get_ptr();

    void dump(std::ostream &out) const;
    template<class Value, class Tracer = EmptyTracer>
    static std::shared_ptr<Value> create(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());

protected:
    XMLNode() = default;
    ~XMLNode() = default;
};


#endif //VALUEBASE_VALUE_H
