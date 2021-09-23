#ifndef KEY_PHRASE_HPP
#define KEY_PHRASE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>

#include <txml/applications/xdxf/KeyPhrase.h>
#include <txml/applications/xdxf/TextElement.hpp>

namespace xdxf
{
const char *KeyPhrase::name() const noexcept
{
    return class_name();
}

const KeyPhrase::value_t &KeyPhrase::getValue() const
{
    auto val = base::get<TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(KeyPhrase::class_name()) + " - no value");
    }
    return val->getValue();
}


template<class Tracer>
void KeyPhrase::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << KeyPhrase::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << KeyPhrase::class_name() << ">\n";
}

template<class Formatter, class Tracer>
void KeyPhrase::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Formatter, class Tracer>
void KeyPhrase::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<KeyPhrase>(tracer);
}
} // namespace xdxf
#endif //KEY_PHRASE_HPP
