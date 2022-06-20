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
    std::cout << fb2::FictionBook::get_path<fb2::FirstName, '!'>() << std::endl;
    return 0;
}
