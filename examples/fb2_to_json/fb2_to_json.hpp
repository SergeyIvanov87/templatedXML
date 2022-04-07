#ifndef FB2_TO_JSON_SERIALIZER_HPP
#define FB2_TO_JSON_SERIALIZER_HPP

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace json
{

TXML_DECLARE_SERIALIZER_CLASS(Fb2ToJSON, ToJSON, FB2_CLASS_LIST)
{
    TXML_SERIALIZER_OBJECT
};
} // namespace json

#endif // FB2_TO_JSON_SERIALIZER_HPP
