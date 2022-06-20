#ifndef TXML_DETAILS_SEARCHABLE_H
#define TXML_DETAILS_SEARCHABLE_H

#include <array>
#include <string_view>
#include <type_traits>

namespace txml
{
template<class U, class ...T>
struct Searchable {

    template <class ToSearch, char sep = '.'>
    static constexpr std::string_view get_path()
    {
        if constexpr(std::is_same_v<ToSearch, U>)
        {
            return U::class_name();
        }
        else
        {
            return BuildPathHelper<ToSearch, sep>::value;
        }
    }

    template <class ToSearch>
    static constexpr bool contains()
    {
        if constexpr(std::is_same_v<ToSearch, U>)
        {
            return true;
        }
        return (T::template contains<ToSearch>() || ... || false);
    }

    template<class TTTT, char sep = '.'>
    struct BuildPathHelper {
    static constexpr auto impl() noexcept
    {
        if constexpr (Searchable<U, T...>::template contains<TTTT>())
        {
            constexpr std::size_t len = U::class_name().size() + 1 +
                                        ((T::template contains<TTTT>() ?
                                            T::template get_path<TTTT, sep>().size() + (std::is_same_v<TTTT, T> ? 0 : 1):
                                            0) + ... + 0) ;
            std::array<char, len + 1> arr{};
            auto append_self = [j = 0, &arr](const std::string_view& s) mutable {
                for (auto c : s) arr[j++] = c;
                arr[j++] = sep;
            };

            auto append = [i = U::class_name().size() + 1, &arr](const std::string_view& s, auto is_same) mutable {
                for (auto c : s) arr[i++] = c;
                if (!s.empty() && std::is_same_v<typename std::decay<decltype(is_same)>::type, std::false_type>) arr[i++]=sep;
            };
            append_self(U::class_name());
            (append((T::template contains<TTTT>() ? T::template get_path<TTTT, sep>() : std::string_view{}), std::is_same_v<TTTT, T>), ...);
            arr[len] = 0;
            return arr;
        }
        else
        {
            return std::array<char,1>{'\0'};
        }
    }

    static constexpr auto arr = impl();

    static constexpr std::string_view value {arr.data(), arr.size() - 1};
    };
////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
    template<class TTTT>
    struct BuildPathHelper {
    static constexpr auto impl() noexcept
    {
        if constexpr (Searchable<U, T...>::template contains<TTTT>())
        {
            constexpr std::size_t len = (T::template get_path<TTTT>().size() + ... + 0) + U::class_name().size();
            std::array<char, len + 1> arr{};
            auto append_self = [j = 0, &arr](const std::string_view& s) mutable {
                for (auto c : s) arr[j++] = c;
            };

            auto append = [i = U::class_name().size(), &arr](const std::string_view& s) mutable {
                for (auto c : s) arr[i++] = c;
            };
            append_self(U::class_name());
            (append(T::template get_path<TTTT>()), ...);
            arr[len] = 0;
            return arr;
        }
        else
        {
            return std::array<char,1>{'\0'};
        }
    }
    static constexpr auto arr = impl();
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
    };
#endif
};

template<class T>
struct Searchable<T> {

    template <class ToSearch, char sep = '.'>
    static constexpr std::string_view get_path()
    {
        if constexpr(std::is_same_v<ToSearch, T>)
        {
            return T::class_name();
        }
        else
        {
            return {};
        }
    }

    template <class ToSearch>
    static constexpr bool contains()
    {
        return std::is_same_v<ToSearch, T>;
    }
};
} // namespace txml
#endif //TXML_DETAILS_SEARCHABLE_H
