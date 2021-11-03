#ifndef TAG_HOLDER_H
#define TAG_HOLDER_H

#include <tuple>
#include <type_traits>

namespace txml
{
template<class ...Tags>
struct TagHolder : public Tags... {};

template<class Tag, class ...HolderTags>
constexpr bool isContainTag(TagHolder<HolderTags...>)
{
    return std::disjunction_v<std::is_same<Tag, HolderTags>...>;
}

struct ArrayTag { };
struct ContainerTag { };
struct LeafTag { };

} // namespace txml
#endif // TAG_HOLDER_H
