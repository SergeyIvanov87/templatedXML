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
public:
    template<class T>
    using ArgumentOptional = std::optional<T>;
    using Tuple = std::tuple<ArgumentOptional<Arguments>...>;
//protected:
    template<class Fabric, class ...CreationArgs>
    size_t create_from(CreationArgs&&... next_args);

    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer>
    void format_serialize_elements(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer>
    static void schema_serialize_elements(Formatter &out, Tracer tracer);

    template<class Element, class Formatter, class Tracer>
    static void schema_serialize_element(Formatter &out, Tracer tracer);

    template<class Formatter, class Tracer>
    size_t format_deserialize_elements(Formatter &in, Tracer tracer);

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

private:
    std::shared_ptr<Tuple> storage;  //TODO make pointer!!!   introduce methods has_value() & value()  as std::optional!

    [[ noreturn ]] void throw_exception() const;

    template<class T>
    [[ noreturn ]] void throw_exception() const;
};
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
