#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <txml/include/utils/Tracer.hpp>
#include <txml/include/details/fwd/GenericContainerImpl.h>
#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>

namespace txml
{
struct TextReaderWrapper;

template<class Impl, class ElementType>
struct XMLArray : public std::enable_shared_from_this<XMLArray<Impl, ElementType>>,
                 public XMLProducible<Impl>,
                 public XMLArrayContainerNode<ElementType>,
                 public XMLSerializable<Impl>,//<XMLArray<Impl, ElementType>>,
                 public XMLFormatSerializable<Impl>, //<XMLArray<Impl, ElementType>>,
                 public XMLFormatDeserializable<Impl>,//XMLArray<Impl, ElementType>>,
                 public XMLSchemaSerializable<Impl>,//<XMLArray<Impl, ElementType>>,
                 public TagHolder<ArrayTag>
{
    using modifiers_t = std::optional<std::vector<std::string>>;
    using Container = XMLArrayContainerNode<ElementType>;
    using tags_t = TagHolder<ArrayTag>;
/*
    static constexpr const char* class_name()
    {
        return "XMLArray";
    }

    static constexpr txml::TextReaderWrapper::NodeType class_node_type()
    {
        return txml::TextReaderWrapper::NodeType::Element;
    };
*/
    std::shared_ptr<XMLArray<Impl, ElementType>> get_ptr();

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
    XMLArray() = default;
    ~XMLArray() = default;
};
} // namespace txml
#endif //XML_ARRAY_H
