#ifndef XML_NODE_LEAF_H
#define XML_NODE_LEAF_H

#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/utils/fwd/utils.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/details/fwd/Searchable.h>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class Impl, class T>
struct XMLNodeLeaf : public XMLFormatSerializable<Impl>,
                     public XMLFormatDeserializable<Impl>,
                     public XMLSchemaSerializable<Impl>,
                     public Searchable<Impl>,
                     public TagHolder<LeafTag>,
                     public TracerHelper<Impl>
{
    using tags_t = TagHolder<LeafTag>;
    using modifiers_t = std::optional<std::vector<std::string>>;
    using value_t = T;

    XMLNodeLeaf(value_t&& v);
    XMLNodeLeaf(const value_t& v = value_t()); /*TODO required default value. Make pointer*/

    const value_t& value() const;
    value_t& value();

    template<class Tracer = EmptyTracer>
    static std::optional<Impl> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_request(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_request(Formatter& out, Tracer tracer = Tracer());
private:
    value_t val;
};
} // namespace txml
#endif //XML_NODE_LEAF_H
