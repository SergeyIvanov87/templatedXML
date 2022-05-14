#ifndef XDXF_KEY_PHRASE_HPP
#define XDXF_KEY_PHRASE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>

#include <txml/applications/xdxf/include/fwd/KeyPhrase.h>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
inline const KeyPhrase::value_t &KeyPhrase::getValue() const
{
    auto val = base::getValue<TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(KeyPhrase::class_name()) + " - no value");
    }
    return val->getValue();
}
} // namespace xdxf
#endif //XDXF_KEY_PHRASE_HPP
