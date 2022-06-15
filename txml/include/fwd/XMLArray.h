#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>
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
                 public XMLSerializable<Impl>,
                 public XMLFormatSerializable<Impl>,
                 public XMLFormatDeserializable<Impl>,
                 public XMLSchemaSerializable<Impl>,
                 public Searchable<Impl, ElementType>,
                 public TagHolder<ArrayTag>,
                 public TracerHelper<Impl>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using ChildNode = std::optional<ElementType>;
    using NodesStorage = std::vector<ChildNode>;

    using tags_t = TagHolder<ArrayTag>;


    XMLArray(NodesStorage &&val);
    XMLArray(const NodesStorage &val);
    XMLArray(std::initializer_list<ChildNode> list);

    const NodesStorage& value() const;
    NodesStorage& value();

    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);


    template<class Tracer = EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;
//////////////
    // actual serialization/deserialization implementations
    // Methods are public because deserializer/serializer can use these
    template<class Formatter, class Tracer>
    void make_format_serialize(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer>
    size_t make_format_deserialize(Formatter &in, Tracer tracer);

////////////////
    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_request(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_request(Formatter& out, Tracer tracer = Tracer());

protected:
    XMLArray() = default;
    ~XMLArray() = default;
private:
    NodesStorage storage;
};
} // namespace txml
#endif //XML_ARRAY_H
