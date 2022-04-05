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

} // namespace utils
} // namespace txml
#endif //  TXML_INCLUDE_UTILS_H
