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
    void create_from(CreationArgs&&... next_args);

    template<class Argument, class Tracer>
    void serialize_impl(std::ostream &out, Tracer tracer) const;

    template<class Tracer, class EndElementManipulator>
    void serialize_elements(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer>
    void format_serialize_elements(Formatter &out, Tracer tracer) const;

    template<class Formatter, class Tracer>
    static void schema_serialize_elements(Formatter &out, Tracer tracer);

    template<class T>
    ArgumentPtr<T> get() const;

    template<class T>
    void set(ArgumentPtr<T> arg);
private:
    Tuple storage;
};
} // namespace txml
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
