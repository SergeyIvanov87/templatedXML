#ifndef TXML_INCLUDE_UTILS_H
#define TXML_INCLUDE_UTILS_H

#include <array>
#include <iostream>
#include <string_view>


#include <txml/txml_fwd.h>

namespace txml
{
namespace utils
{

template <std::string_view const&... strings>
struct join
{
    static constexpr auto impl() noexcept
    {
        constexpr std::size_t len = (strings.size() + ... + 0);
        std::array<char, len + 1> arr{};
        auto append = [i = 0, &arr](auto const& s) mutable {
            for (auto c : s) arr[i++] = c;
        };
        (append(strings), ...);
        arr[len] = 0;
        return arr;
    }
    // Give the joined string static storage
    static constexpr auto arr = impl();
    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
};
// Helper to get the value out
template <const std::string_view &... strings>
static constexpr auto join_v = join<strings...>::value;


template <char begin, char sep, char endl, class ...Node>
struct join_node_names
{
    static constexpr auto impl() noexcept
    {
        constexpr std::size_t len = (Node::class_name().size() + ... + 0) + sizeof...(Node)  + 1; // + begin + sep + endl
        std::array<char, len + 1> arr{};
        arr[0] = begin;
        auto append = [i = 1, &arr](auto const& s) mutable {
            for (auto c : s) arr[i++] = c;
            arr[i++] = sep;
        };
        (append(Node::class_name()), ...);
        arr[len-1] = endl;
        arr[len] = 0;
        return arr;
    }
    // Give the joined string static storage
    static constexpr auto arr = impl();
    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
};
// Helper to get the value out
template <char begin, char sep, char endl, class ...Node>
static constexpr auto join_node_names_v = join_node_names<begin, sep, endl, Node...>::value;


template<class T, class ...U>
struct core_t_extractor
{
    using type = std::enable_if_t<std::conjunction_v<std::is_same<typename U::core_t, typename T::core_t>...>, typename T::core_t>;
};

template<class T, class ...U>
using core_t_extractor_t = typename core_t_extractor<T, U...>::type;

template<class T, class ...U>
struct in_stream_core_t_extractor
{
    using type = std::enable_if_t<std::conjunction_v<std::is_same<typename U::in_stream_core_t,
                                                                  typename T::in_stream_core_t>...>,
                                  typename T::in_stream_core_t>;
};

template<class T, class ...U>
using in_stream_core_t_extractor_t = typename in_stream_core_t_extractor<T, U...>::type;

namespace
{
template <class t>
inline void hash_combine(std::size_t& seed, t const& v)
{
seed ^= std::hash<t>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
template <class tuple,
size_t index = std::tuple_size<tuple>::value - 1>
struct hashvalueimpl
{
static void apply(size_t& seed, tuple const& t)
{
hashvalueimpl<tuple, index-1>::apply(seed, t);
hash_combine(seed, get<index>(t));
}
};
template <class tuple>
struct hashvalueimpl<tuple,0>
{
static void apply(size_t& seed, tuple const& t)
{
hash_combine(seed, get<0>(t));
}
};
}
template <typename tt>
struct hash {};

template <typename ... tt>
struct hash<std::tuple<tt...>>
{
size_t
operator()(std::tuple<tt...> const& t) const
{
size_t seed = 0;
hashvalueimpl<std::tuple<tt...> >::apply(seed, t);
return seed;
}
};

} // namespace utils
} // namespace txml
#endif //  TXML_INCLUDE_UTILS_H
