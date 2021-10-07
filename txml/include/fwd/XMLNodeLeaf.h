#ifndef XDXF_TYPED_VALUE_H
#define XDXF_TYPED_VALUE_H

#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/utils/Tracer.hpp>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class T>
struct XMLNodeLeaf : public std::enable_shared_from_this<XMLNodeLeaf<Impl, T>>
{
    using base = std::enable_shared_from_this<XMLNodeLeaf<Impl, T>>;
    using modifiers_t = std::optional<std::vector<std::string>>;
    using value_t = T;

    XMLNodeLeaf(value_t&& v);
    virtual const char *name() const noexcept = 0;

    std::shared_ptr<XMLNodeLeaf<Impl, T>> get_ptr();

    const value_t& getValue() const;
    value_t& getValue();

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Impl> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);
private:
    value_t val;
};
} // namespace txml
#endif //XDXF_TYPED_VALUE_H
