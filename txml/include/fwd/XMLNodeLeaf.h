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

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class T>
struct XMLNodeLeaf : public std::enable_shared_from_this<XMLNodeLeaf<Impl, T>>,
                     public XMLFormatSerializable<Impl>,
                     public XMLFormatDeserializable<Impl>,
                     public XMLSchemaSerializable<Impl>
{
    using base = std::enable_shared_from_this<XMLNodeLeaf<Impl, T>>;
    using modifiers_t = std::optional<std::vector<std::string>>;
    using value_t = T;

    XMLNodeLeaf(value_t&& v);
    virtual const char *name() const noexcept;

    std::shared_ptr<XMLNodeLeaf<Impl, T>> get_ptr();

    const value_t& getValue() const;
    value_t& getValue();

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<Impl> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Impl> format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
private:
    value_t val;
};
} // namespace txml
#endif //XDXF_TYPED_VALUE_H
