#ifndef GENERIC_COMMANDARGUMENTS_VALUE_H
#define GENERIC_COMMANDARGUMENTS_VALUE_H

#include <memory>
#include <tuple>

namespace txml
{
template<class ...Arguments>
class ArgumentContainerBase
{
public:
    template<class T>
    using ArgumentPtr = std::shared_ptr<T>;
    using Tuple = std::tuple<ArgumentPtr<Arguments>...>;

    template<class Fabric, class ...CreationArgs>
    bool create_from(CreationArgs&&... next_args);

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

    template<class T>
    ArgumentPtr<T> getValue() const;

    template<class T>
    ArgumentPtr<T> set(ArgumentPtr<T> arg);

    template<class T, class ...Args>
    ArgumentPtr<T> emplace(Args&& ...args);
private:
    Tuple storage;
};
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
