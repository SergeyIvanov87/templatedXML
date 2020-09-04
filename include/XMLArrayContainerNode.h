#ifndef XDXF_ARRAY_CONTAINER_NODE_H
#define XDXF_ARRAY_CONTAINER_NODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <utils/Tracer.hpp>
#include "XMLProducible.h"

inline std::ostream& no_sep (std::ostream& os);

template<class Value>
struct XMLArrayContainerNode : public XMLProducible<Value>,
                               public XMLNodeLeaf<std::vector<std::shared_ptr<Value>>>
{
    using producible_base = XMLProducible<Value>;
    using base = XMLNodeLeaf<std::vector<std::shared_ptr<Value>>>;

    //use tag name as child type
    static constexpr const char *class_name()
    {
        return Value::class_name();
    }

    //use node type as child type
    static constexpr xmlpp::TextReader::NodeType class_node_type()
    {
        return Value::class_node_type();
    }

    XMLArrayContainerNode(typename base::value_t &&val);

    const char *name() const noexcept override;

    template<class Tracer = EmptyTracer>
    static std::shared_ptr<XMLArrayContainerNode<Value>> create_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer = Tracer());
};

#endif //XDXF_PUBLISHING_H
