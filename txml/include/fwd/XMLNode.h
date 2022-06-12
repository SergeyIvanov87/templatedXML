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
                 public ArgumentContainerBase<ContainedValues...>,
                 public XMLSerializable<Impl>,
                 public XMLFormatSerializable<Impl>,
                 public XMLFormatDeserializable<Impl>,
                 public XMLSchemaSerializable<Impl>,
                 public Searchable<Impl, ContainedValues...>,
                 public TagHolder<ContainerTag>,
                 public TracerHelper<Impl>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;
    using Tuple = typename Container::Tuple;

    using Container::storage;
    using tags_t = TagHolder<ContainerTag>;

    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);

/* TODO  consider remove  void serialize_impl(std::ostream &out) const;*/

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_request(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_request(Formatter& out, Tracer tracer = Tracer());


    // actual serialization/deserialization implementations
    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter &out, Tracer tracer);

    template<class Element, class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer = txml::EmptyTracer>
    size_t format_deserialize_impl(Formatter &in, Tracer tracer);

protected:
    XMLNode() = default;
    ~XMLNode() = default;
};
} // namespace txml
#endif //XML_NODE_H
