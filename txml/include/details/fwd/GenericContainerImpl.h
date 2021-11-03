#ifndef XDXF_ARRAY_CONTAINER_NODE_H
#define XDXF_ARRAY_CONTAINER_NODE_H

#include <memory>
#include <ostream>
#include <vector>

#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/utils/Tracer.hpp>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLArrayContainerNode
{
    using aggregared_t = XMLNodeLeaf<XMLArrayContainerNode<Value>,
                                                  std::vector<std::shared_ptr<Value>>>;

    static constexpr const char* class_name()
    {
        return "Container";
    }

    template<class Fabric, class ...CreationArgs>
    bool create_from(CreationArgs&&... next_args);

    XMLArrayContainerNode(typename aggregared_t::value_t &&val);
    XMLArrayContainerNode() = default;

    const typename aggregared_t::value_t& getValue() const;
    typename aggregared_t::value_t& getValue();

    template<class Tracer = EmptyTracer>
    void serialize_impl(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer>
    void format_serialize_elements(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer>
    static void schema_serialize_elements(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer>
    size_t format_deserialize_elements(Formatter &in, Tracer tracer);
    aggregared_t leaf_node;
};
} // namespace txml
#endif //XDXF_ARRAY_CONTAINER_NODE_H