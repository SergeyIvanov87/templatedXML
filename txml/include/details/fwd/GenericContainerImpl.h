#ifndef XDXF_ARRAY_CONTAINER_NODE_H
#define XDXF_ARRAY_CONTAINER_NODE_H

#include <optional>
#include <ostream>
#include <vector>

#include <txml/include/fwd/XMLProducible.h>
#include <txml/include/fwd/XMLNodeLeaf.h>
#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>

#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

namespace txml
{
inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLArrayContainerNode
{
    using aggregared_t = XMLNodeLeaf<XMLArrayContainerNode<Value>,
                                     std::vector<std::optional<Value>>>;

    static constexpr std::string_view class_name()
    {
        return "Container";
    }

    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);

    XMLArrayContainerNode(typename aggregared_t::value_t &&val);
    XMLArrayContainerNode(std::initializer_list<typename aggregared_t::value_t::value_type> list);
    XMLArrayContainerNode() = default;

    const typename aggregared_t::value_t& value() const;
    typename aggregared_t::value_t& value();

    template<class Tracer = EmptyTracer>
    void make_xml_serialize(std::ostream &out, Tracer tracer = Tracer()) const;

    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer>
    void make_format_serialize(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer>
    static void make_schema_serialize(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer>
    size_t make_format_deserialize(Formatter &in, Tracer tracer);
    aggregared_t leaf_node;
};
} // namespace txml
#endif //XDXF_ARRAY_CONTAINER_NODE_H
