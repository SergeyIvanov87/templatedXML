#ifndef XML_NODE_H
#define XML_NODE_H

#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>
#include <txml/include/details/GenericCommandArguments.h>
#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/details/fwd/Searchable.h>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class Impl, class ...ContainedValues>
struct XMLNode : public XMLProducible<Impl>,
                 public XMLSerializable<Impl>,
                 public XMLFormatSerializable<Impl>,
                 public XMLFormatDeserializable<Impl>,
                 public XMLSchemaSerializable<Impl>,
                 public Searchable<Impl, ContainedValues...>,
                 public TagHolder<ContainerTag>,
                 public TracerHelper<Impl>
{
    friend class XMLFormatSerializable<Impl>;
    friend class XMLFormatDeserializable<Impl>;
    friend class XMLSchemaSerializable<Impl>;
    friend class XMLSerializable<Impl>;

    using modifiers_t = std::optional<std::vector<std::string>>;

    template<class T>
    using ChildNode = std::optional<T>;
    using NodesStorage = std::tuple<ChildNode<ContainedValues>...>;

    using tags_t = TagHolder<ContainerTag>;

    XMLNode(const XMLNode &src);
    XMLNode(XMLNode &&src);

    template<class ...SpecificContainedValues>
    XMLNode(const SpecificContainedValues & ...args);

    template<class ...SpecificContainedValues>
    XMLNode(const std::optional<SpecificContainedValues> & ...args);

    XMLNode &operator=(const XMLNode &src);
    XMLNode &operator=(XMLNode &&src);

    /* Data access interface */
    bool has_data() const;
    const NodesStorage& data() const;
    NodesStorage& data();

    // Node value access
    template<class T>
    bool has_value() const;
    template<class T>
    const T& value() const;
    template<class T>
    T& value();

    // Node acccess
    template<class T>
    const ChildNode<T>& node() const;
    template<class T, class ...Args>
    ChildNode<T>& node_or(Args &&...args);

    // Node creation
    template<class T>
    ChildNode<T>& insert(const ChildNode<T>& arg, bool overwrite = true);

    template<class T>
    ChildNode<T>& insert(ChildNode<T>&& arg, bool overwrite = true);

    template<class T, class ...Args>
    ChildNode<std::decay_t<T>>& emplace(Args&& ...args);

    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);

    // actual serialization/deserialization implementations
    // Methods are public because deserializer/serializer can use these
    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void make_format_serialize(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Element, class Formatter, class Tracer = txml::EmptyTracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer = txml::EmptyTracer>
    size_t make_format_deserialize(Formatter &in, Tracer tracer);

/* TODO  consider remove  void make_xml_serialize(std::ostream &out) const;*/
private:
    template<class Tracer = txml::EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_request(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_request(Formatter& out, Tracer tracer = Tracer());

    [[ noreturn ]] void throw_exception() const;

    template<class T>
    [[ noreturn ]] void throw_exception() const;

    std::shared_ptr<NodesStorage> storage;
protected:
    XMLNode() = default;
    ~XMLNode() = default;
};
} // namespace txml
#endif //XML_NODE_H
