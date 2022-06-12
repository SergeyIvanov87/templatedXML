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
    using ArgumentOptional = std::optional<T>;
    using Tuple = std::tuple<ArgumentOptional<Arguments>...>;

public:
    bool has_data() const;

    const Tuple& data() const;
    Tuple& data();

    template<class T>
    bool has_value() const;

    template<class T>
    const T& value() const;

    template<class T>
    T& value();


    template<class T>
    const ArgumentOptional<T>& node() const;

    template<class T, class ...Args>
    ArgumentOptional<T>& node_or(Args &&...args);


    template<class T>
    ArgumentOptional<T>& insert(const ArgumentOptional<T>& arg, bool overwrite = true);

    template<class T>
    ArgumentOptional<T>& insert(ArgumentOptional<T>&& arg, bool overwrite = true);

    template<class T, class ...Args>
    ArgumentOptional<std::decay_t<T>>& emplace(Args&& ...args);

protected:
    std::shared_ptr<Tuple> storage;  //TODO make pointer!!!   introduce methods has_value() & value()  as std::optional!

private:
    [[ noreturn ]] void throw_exception() const;

    template<class T>
    [[ noreturn ]] void throw_exception() const;
};
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
