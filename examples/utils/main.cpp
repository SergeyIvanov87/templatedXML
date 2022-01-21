#include <iostream>

#include <txml/applications/fb2/fb2.hpp>
#include <txml/include/utils/fwd/utils.h>

enum eLogLevel : int
{
    ERROR_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL,
    TRACE_LEVEL
};
#if 0
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

#endif
struct Foo {};
struct A_1: public txml::Searchable<A_1> {
    static constexpr std::string_view class_name() {return  "A_1_class_a";}
};

struct A_2: public txml::Searchable<A_2> {
    static constexpr std::string_view class_name() {return  "A_2_class_aa";}
};

struct A_3: public txml::Searchable<A_3> {
    static constexpr std::string_view class_name() {return  "A_3_class_aaa";}
};

struct B_1: public txml::Searchable<B_1, A_1> {
    static constexpr std::string_view class_name () {return  "B_1_class_b";}
};

struct B_12: public txml::Searchable<B_12, A_1, A_2> {
    static constexpr std::string_view class_name() {return "B_12_class_bb";}
};

struct B_123: public txml::Searchable<B_123, A_1, A_2, A_3> {
    static constexpr std::string_view class_name() {return "B_123_class_bbb";}
};

struct C_123: public txml::Searchable<C_123, B_1, B_12, B_123> {
    static constexpr std::string_view class_name() {return "C_123_class_cccccc";}
};

struct D_123: public txml::Searchable<D_123, B_123> {
    static constexpr std::string_view class_name() {return "D_123_class_cccccc";}
};

template<class Req>
struct Test
{
    static constexpr std::string_view class_name() { return D_123::get_path<Req, ','>(); }
};
int main(int argc, char** argv)
{
    using namespace txml;
    using namespace fb2;

    if (argc < 2)
    {
        perror("need file name");
        return -1;
    }

    eLogLevel log_level = eLogLevel::ERROR_LEVEL;
    if (argc > 2)
    {
        log_level = static_cast<eLogLevel>(std::max(std::atoi(argv[2]), static_cast<std::underlying_type_t<eLogLevel>>(eLogLevel::ERROR_LEVEL)));
    }

    static_assert(A_1::contains<A_1>(), "A_1 for A_1 must be positive");
    std::cout << "A_1 for A_1: " << A_1::get_path<A_1>() << std::endl;

    static_assert(B_1::contains<B_1>(), "B_1 for B_1 must be positive");
    std::cout << "B_1 for B_1: " << B_1::get_path<B_1>() << std::endl;


    static_assert(B_1::contains<A_1>(), "B_1 for A_1 must be positive");
    std::cout << "B_1 for A_1: " << B_1::get_path<A_1>() << std::endl;
    static_assert(!B_1::contains<A_2>(), "B_1 for A_2 must be negative");
    std::cout << "B_1 for A_2: " << B_1::get_path<A_2>() << std::endl;

    static_assert(B_12::contains<B_12>(), "B_12 for B_12 must be positive");
    std::cout << "B_12 for B_12: " << B_12::get_path<B_12>() << std::endl;

    static_assert(B_12::contains<A_1>(), "B_12 for A_1 must be positive");
    std::cout << "B_12 for A_1: " << B_12::get_path<A_1>() << std::endl;

    static_assert(B_12::contains<A_2>(), "B_12 for A_2 must be positive");
    std::cout << "B_12 for A_2: " << B_12::get_path<A_2>() << std::endl;
    static_assert(!B_12::contains<A_3>(), "B_12 for A_3 must be negative");
    std::cout << "B_12 for A_3: " << B_12::get_path<A_3>() << std::endl;

    std::cout << "B_123 for B_123: " << B_123::get_path<B_123>() << std::endl;

    static_assert(B_123::contains<A_1>(), "B_123 for A_1 must be positive");
    std::cout << "B_123 for A_1: " << B_123::get_path<A_1>() << std::endl;

    static_assert(B_123::contains<A_2>(), "B_123 for A_2 must be positive");
    std::cout << "B_123 for A_2: " << B_123::get_path<A_2>() << std::endl;

    static_assert(B_123::contains<A_3>(), "B_123 for A_3 must be positive");
    std::cout << "B_123 for A_3: " << B_123::get_path<A_3>() << std::endl;

    static_assert(C_123::contains<A_1>(), "C_123 for A_1 must be positive");
    std::cout << "C_123 for A_1: " << C_123::get_path<A_1>() << std::endl;

    static_assert(C_123::contains<A_2>(), "C_123 for A_2 must be positive");
    std::cout << "C_123 for A_2: " << C_123::get_path<A_2>() << std::endl;

    static_assert(C_123::contains<A_3>(), "C_123 for A_3 must be positive");
    std::cout << "C_123 for A_3: " << C_123::get_path<A_3>() << std::endl;

    static_assert(D_123::contains<A_3>(), "C_123 for A_3 must be positive");
    std::cout << "D_123 for A_3: " << D_123::get_path<A_3>() << std::endl;


    std::cout << Test<A_3>::class_name() << std::endl;
    return 0;
}
