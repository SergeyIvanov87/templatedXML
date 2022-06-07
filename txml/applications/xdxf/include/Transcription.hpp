#ifndef TRANSCRIPTION_HPP
#define TRANSCRIPTION_HPP

#include <iostream>

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/XMLCreator.hpp>

#include <txml/applications/xdxf/include/fwd/Transcription.h>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
inline const Transcription::value_t &Transcription::value() const
{
    const auto& val = base::node<TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Transcription::class_name()) + " - no value");
    }
    return val->value();
}
} // namespace xdxf
#endif //TRANSCRIPTION_HPP
