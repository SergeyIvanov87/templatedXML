#ifndef GENERIC_COMMANDARGUMENTS_VALUE_H
#define GENERIC_COMMANDARGUMENTS_VALUE_H

#include <memory>
#include <optional>
#include <tuple>

#include <txml/include/utils/fwd/utils.h>

namespace txml
{
template<class ...Arguments>
class ArgumentContainerBase
{
protected:
    template<class T>
    using ChildNode = std::optional<T>;
    using NodesStorage = std::tuple<ChildNode<Arguments>...>;
/*
public:
    bool has_data() const;

    const NodesStorage& data() const;
    NodesStorage& data();

    template<class T>
    bool has_value() const;

    template<class T>
    const T& value() const;

    template<class T>
    T& value();


    template<class T>
    const ChildNode<T>& node() const;

    template<class T, class ...Args>
    ChildNode<T>& node_or(Args &&...args);


    template<class T>
    ChildNode<T>& insert(const ChildNode<T>& arg, bool overwrite = true);

    template<class T>
    ChildNode<T>& insert(ChildNode<T>&& arg, bool overwrite = true);

    template<class T, class ...Args>
    ChildNode<std::decay_t<T>>& emplace(Args&& ...args);
*/
protected:
    std::shared_ptr<NodesStorage> storage;  //TODO make pointer!!!   introduce methods has_value() & value()  as std::optional!

private:
    [[ noreturn ]] void throw_exception() const;

    template<class T>
    [[ noreturn ]] void throw_exception() const;
};
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
