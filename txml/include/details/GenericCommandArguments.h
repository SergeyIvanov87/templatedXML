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
    using ArgumentPtr = std::optional<T>;
    using Tuple = std::tuple<ArgumentPtr<Arguments>...>;

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

    template<class T>
    ArgumentPtr<T> getValue() const;

    const Tuple& getValue() const;
    Tuple& getValue();

    template<class T>
    ArgumentPtr<T> set(ArgumentPtr<T> arg);

    template<class T, class ...Args>
    ArgumentPtr<std::decay_t<T>> emplace(Args&& ...args);

    bool has_value() const;
private:
    std::shared_ptr<Tuple> storage;  //TODO make pointer!!!   introduce methods has_value() & value()  as std::optional!
};
} // namespace txml


////////////
namespace std {
template <typename ... tt>
struct hash<txml::ArgumentContainerBase<tt...>>
{
size_t
operator()(txml::ArgumentContainerBase<tt...> const& t) const
{
return txml::utils::hash<typename txml::ArgumentContainerBase<tt...>::Tuple>() (t.has_value() ? t.getValue() : typename txml::ArgumentContainerBase<tt...>::Tuple{} );
}
};
}
////////////
#endif //GENERIC_COMMANDARGUMENTS_VALUE_H
