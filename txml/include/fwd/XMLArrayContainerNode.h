#ifndef XDXF_ARRAY_CONTAINER_NODE_H
#define XDXF_ARRAY_CONTAINER_NODE_H

#include <memory>
#include <ostream>
#include <vector>

#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/utils/Tracer.hpp>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLArrayContainerNode : public XMLProducible<Value>,
                               public XMLSerializable<XMLArrayContainerNode<Value>>,
                               public XMLSchemaSerializable<XMLArrayContainerNode<Value>>,
                               public XMLFormatDeserializable<XMLArrayContainerNode<Value>>,
                               public TagHolder<ArrayTag>
{
    using producible_base = XMLProducible<Value>;
    using aggregared_t = XMLNodeLeaf<XMLArrayContainerNode<Value>,
                                                  std::vector<std::shared_ptr<Value>>>;
    using tags_t = TagHolder<ArrayTag>;

    //use tag name as child type
    static constexpr const char *class_name()
    {
        return Value::class_name();
    }

    //use node type as child type
    static constexpr TextReaderWrapper::NodeType class_node_type()
    {
        return Value::class_node_type();
    }

    XMLArrayContainerNode(typename aggregared_t::value_t &&val);

    const char *name() const noexcept;

    const typename aggregared_t::value_t& getValue() const;
    typename aggregared_t::value_t& getValue();

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<XMLArrayContainerNode<Value>> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer = Tracer());


    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::shared_ptr<XMLArrayContainerNode<Value>>
    format_deserialize_impl(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_impl(Formatter& in, Tracer tracer = Tracer());

    aggregared_t leaf_node;
};
} // namespace txml
#endif //XDXF_ARRAY_CONTAINER_NODE_H
