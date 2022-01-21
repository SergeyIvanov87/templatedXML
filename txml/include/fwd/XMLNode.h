#ifndef XML_NODE_H
#define XML_NODE_H

#include <memory>
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

namespace txml
{
template<class Impl, class ...ContainedValues>
struct XMLNode : public std::enable_shared_from_this<XMLNode<Impl, ContainedValues...>>,
                 public XMLProducible<Impl>,
                 public ArgumentContainerBase<ContainedValues...>,
                 public XMLSerializable<Impl>,
                 public XMLFormatSerializable<Impl>,
                 public XMLFormatDeserializable<Impl>,
                 public XMLSchemaSerializable<Impl>,
                 public Searchable<Impl, ContainedValues...>,
                 public TagHolder<ContainerTag>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;
    using tags_t = TagHolder<ContainerTag>;

    std::shared_ptr<XMLNode<Impl, ContainedValues...>> get_ptr();

    template<class Tracer = txml::EmptyTracer>
    bool initialize(TextReaderWrapper &reader, Tracer tracer = Tracer());

    void serialize_impl(std::ostream &out) const;

    template<class Tracer = txml::EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_impl(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<Impl> format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());

protected:
    XMLNode() = default;
    ~XMLNode() = default;
};
} // namespace txml
#endif //XML_NODE_H
