#ifndef XDXF_TYPED_VALUE_H
#define XDXF_TYPED_VALUE_H

#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/details/fwd/Searchable.h>

namespace txml
{
template<class Impl, class T>
struct XMLNodeLeaf : public XMLFormatSerializable<Impl>,
                     public XMLFormatDeserializable<Impl>,
                     public XMLSchemaSerializable<Impl>,
                     public Searchable<Impl>,
                     public TagHolder<LeafTag>
{
    using tags_t = TagHolder<LeafTag>;
    using modifiers_t = std::optional<std::vector<std::string>>;
    using value_t = T;

    XMLNodeLeaf(value_t&& v);
    XMLNodeLeaf(const value_t& v = value_t()); /*TODO required default value. Make pointer*/

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
