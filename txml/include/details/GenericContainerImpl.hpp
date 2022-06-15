#ifndef XDXF_ARRAY_CONTAINER_NODE_HPP
#define XDXF_ARRAY_CONTAINER_NODE_HPP


#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLNodeLeaf.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

namespace txml
{
template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(typename aggregared_t::value_t &&val) :
    leaf_node(std::move(val))
{
}

template<class Value>
XMLArrayContainerNode<Value>::XMLArrayContainerNode(std::initializer_list<typename aggregared_t::value_t::value_type> list) :
    XMLArrayContainerNode(typename aggregared_t::value_t {list})
{
}

template<class Value>
template<class Fabric, class ...CreationArgs>
size_t XMLArrayContainerNode<Value>::create_from(CreationArgs&&... next_args)
{
    typename aggregared_t::value_t &arr = leaf_node.value();
    std::optional<Value> elem;
    do {
        elem = Fabric::template try_create<Value>(std::forward<CreationArgs>(next_args)...);
        if (elem) {
            arr.push_back(elem);
        }
    } while (elem);
    return arr.size();
}
} // namespace txml
#endif //XDXF_CREATOR_H
