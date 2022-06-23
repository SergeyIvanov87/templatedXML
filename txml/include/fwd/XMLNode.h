#ifndef XML_NODE_H
#define XML_NODE_H

#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>
#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/details/fwd/Searchable.h>
#include <txml/include/engine/fwd/TracerHelper.h>
#include <txml/include/utils/fwd/utils.h>

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

    template<class ...SpecificContainedValues,
             class = std::enable_if_t<std::conjunction_v<txml::utils::is_in<
                                                            utils::decay_optional_t<SpecificContainedValues>,
                                                            ContainedValues...>...>, int>>
    XMLNode(const SpecificContainedValues & ...args);
    XMLNode &operator=(const XMLNode &src);
    XMLNode &operator=(XMLNode &&src);

    // SFINAE compilation breaking constructors
    template<class ...SpecificContainedValues,
             std::enable_if_t<std::disjunction_v<txml::utils::is_not_in<utils::decay_optional_t<SpecificContainedValues>, ContainedValues...>...>, char> = 0>
    XMLNode(const SpecificContainedValues & ...)
    {
        static_assert(std::conjunction_v<txml::utils::is_in<utils::decay_optional_t<SpecificContainedValues>, ContainedValues...>...>,
                      "XMLNode variadic constructor `SpecificContainedValues` types must be subset of 'ContainedValues' types");
    }

    /* Data access interface */
    bool empty() const;
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
    std::pair<std::reference_wrapper<ChildNode<T>>, bool> insert(const ChildNode<T>& arg);

    template<class T>
    std::pair<std::reference_wrapper<ChildNode<T>>, bool> insert(ChildNode<T>&& arg);

    template<class T, class ...Args>
    std::pair<std::reference_wrapper<ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool> emplace(Args&& ...args);

    template<class T, class U>
    std::pair<std::reference_wrapper<ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool> emplace(ChildNode<U>&& node);

    template<class T, class U>
    std::pair<std::reference_wrapper<ChildNode<std::decay_t<utils::decay_optional_t<std::decay_t<T>>>>>, bool> emplace(const ChildNode<U> &node);


    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);

    // actual serialization/deserialization implementations
    // Methods are public because deserializer/serializer can use these
    template<class Formatter, class Tracer = txml::EmptyTracer>
    void make_format_serialize(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Element, class Formatter, class Tracer = txml::EmptyTracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer = txml::EmptyTracer>
    size_t make_format_deserialize(Formatter &in, Tracer tracer);

protected:
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

    XMLNode() = default;
    ~XMLNode() = default;
};
} // namespace txml
#endif //XML_NODE_H
