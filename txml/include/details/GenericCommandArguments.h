#ifndef GENERIC_COMMANDARGUMENTS_VALUE_H
#define GENERIC_COMMANDARGUMENTS_VALUE_H

#include <memory>
#include <tuple>

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
    void dump(std::ostream &out, Tracer tracer) const;

    template<class Tracer, class EndElementManipulator>
    void dump_all(std::ostream &out, Tracer tracer, EndElementManipulator sep) const;

    template<class Formatter, class Tracer>
    void format_dump_all(Formatter &out, Tracer tracer) const;

    template<class T>
    ArgumentPtr<T> get() const;

    template<class T>
    void set(ArgumentPtr<T> arg);
private:
    Tuple storage;
};
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
