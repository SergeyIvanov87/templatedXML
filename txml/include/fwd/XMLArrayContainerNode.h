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
#include <txml/include/utils/Tracer.hpp>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLArrayContainerNode : public XMLProducible<Value>,
                               public XMLNodeLeaf<std::vector<std::shared_ptr<Value>>>,
                               public XMLSerializable<XMLArrayContainerNode<Value>>,
                               public XMLSchemaSerializable<XMLArrayContainerNode<Value>>
{
    using producible_base = XMLProducible<Value>;
    using base = XMLNodeLeaf<std::vector<std::shared_ptr<Value>>>;

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

    XMLArrayContainerNode(typename base::value_t &&val);

    const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<XMLArrayContainerNode<Value>> create_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(std::string &name, TextReaderWrapper &reader, Tracer tracer = Tracer());


    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = EmptyTracer>
    static void schema_serialize_impl(Formatter& out, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XDXF_ARRAY_CONTAINER_NODE_H
