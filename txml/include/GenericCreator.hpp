#ifndef GENERIC_CREATOR_HPP
#define GENERIC_CREATOR_HPP

#include <txml/include/fwd/GenericCreator.h>

namespace txml
{
template<class Value, class ...SpecificContainedValues>
std::optional<Value> GenericCreator::try_create(SpecificContainedValues &&...args)
{
    bool non_empty = utils::has::value(args...);
    return non_empty ? std::make_optional<Value>(std::forward<SpecificContainedValues>(args)...) : std::optional<Value>();
}

template<class Value, class Value2, class ...SpecificContainedValues, class ...OtherValues>
std::optional<Value> GenericCreator::try_create(const XMLNode<Value2, SpecificContainedValues...> &n, OtherValues&& ...args)
{
    bool non_empty = utils::has::value(args...) || utils::has::value(n.template node<SpecificContainedValues>()...);
    return non_empty ? std::make_optional<Value>(std::forward<OtherValues>(args)..., n.template node<SpecificContainedValues>()...) : std::optional<Value>();
}
} // namespace txml
#endif //GENERIC_CREATOR_HPP
