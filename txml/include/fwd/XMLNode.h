#ifndef XDXF_VALUEBASE_H
#define XDXF_VALUEBASE_H

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/utils/Tracer.hpp>
#include <txml/include/details/GenericCommandArguments.h>
#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class ...ContainedValues>
struct XMLNode : public std::enable_shared_from_this<XMLNode<Impl, ContainedValues...>>,
                 public XMLProducible<Impl>,
                 public ArgumentContainerBase<ContainedValues...>,
                 public XMLSerializable<XMLNode<Impl, ContainedValues...>>,
                 public XMLFormatSerializable<XMLNode<Impl, ContainedValues...>>,
                 public XMLFormatDeserializable<Impl>,//XMLNode<Impl, ContainedValues...>>,
                 public XMLSchemaSerializable<XMLNode<Impl, ContainedValues...>>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = ArgumentContainerBase<ContainedValues...>;

    virtual const char *name() const noexcept = 0;

    static constexpr const char* class_name()
    {
        return "XMLNode";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };

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
#endif //VALUEBASE_VALUE_H
