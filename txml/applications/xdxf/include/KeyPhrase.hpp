#ifndef XDXF_KEY_PHRASE_HPP
#define XDXF_KEY_PHRASE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

#include <txml/applications/xdxf/include/fwd/KeyPhrase.h>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
inline const KeyPhrase::value_t &KeyPhrase::value() const
{
    if (!base::has_value<TextElement>())
    {
        throw std::runtime_error(std::string(KeyPhrase::class_name()) + " - no value");
    }
    return base::value<TextElement>().value();
}
} // namespace xdxf
#endif //XDXF_KEY_PHRASE_HPP
