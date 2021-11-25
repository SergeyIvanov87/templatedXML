#ifndef TXML_APPLICATION_JSON_UTILS_HPP
#define TXML_APPLICATION_JSON_UTILS_HPP

#include <nlohmann/json.hpp>

namespace json
{
namespace utils
{
template<class T>
static constexpr nlohmann::json::value_t type_to_json_type();



// Impl
// TODO naive mapping
template<>
constexpr nlohmann::json::value_t type_to_json_type<bool>()
{ return nlohmann::json::value_t::boolean; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<std::string>()
{ return nlohmann::json::value_t::string; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<int>()
{ return nlohmann::json::value_t::number_integer; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<uint>()
{ return nlohmann::json::value_t::number_unsigned; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<float>()
{ return nlohmann::json::value_t::number_float; }

template<>
constexpr nlohmann::json::value_t type_to_json_type<double>()
{ return nlohmann::json::value_t::number_float; }


inline const char* json_type_to_cstring(nlohmann::json::value_t type)
{
    switch(type)
    {
        case nlohmann::json::value_t::null:
            return "null";
        case nlohmann::json::value_t::boolean:
            return "boolean";
        case nlohmann::json::value_t::string:
            return "string";
        case nlohmann::json::value_t::number_integer:
            return "number (integer)";
        case nlohmann::json::value_t::number_unsigned:
            return "number (unsigned integer)";
        case nlohmann::json::value_t::number_float:
            return "number (floating-point)";
        case nlohmann::json::value_t::object:
            return "object";
        case nlohmann::json::value_t::array:
            return "array";
        case nlohmann::json::value_t::discarded:
            return "discarded";
        default:
            return "<unknown>";
    }
}
} // namespace utils
} // namespace json
#endif // TXML_APPLICATION_JSON_UTILS_HPP
