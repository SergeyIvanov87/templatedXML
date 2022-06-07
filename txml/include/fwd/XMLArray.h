#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>
#include <txml/include/details/fwd/GenericContainerImpl.h>
#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/details/fwd/Searchable.h>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class ElementType>
struct XMLArray: public XMLProducible<Impl>,
                 public XMLArrayContainerNode<ElementType>,
                 public XMLSerializable<Impl>,
                 public XMLFormatSerializable<Impl>,
                 public XMLFormatDeserializable<Impl>,
                 public XMLSchemaSerializable<Impl>,
                 public Searchable<Impl, ElementType>,
                 public TagHolder<ArrayTag>,
                 public TracerHelper<Impl>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = XMLArrayContainerNode<ElementType>;
    using tags_t = TagHolder<ArrayTag>;

    using Container::Container;

    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    void serialize_impl(std::ostream &out) const;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());

protected:
    XMLArray() = default;
    ~XMLArray() = default;
};
} // namespace txml
#endif //XML_ARRAY_H
