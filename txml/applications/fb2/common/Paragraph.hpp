#ifndef FB2_PARAGRAPH_HPP
#define FB2_PARAGRAPH_HPP
#include <iostream>

#include "fb2/common/Paragraph.h"
#include "fb2/FB2TextElement.hpp"
#include "XMLProducible.hpp"
#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"

const char *Paragraph::name() const noexcept
{
    return class_name();
}

const Paragraph::value_t &Paragraph::getValue() const
{
    auto val = base::get<FB2TextElement>();
    if (!val)
    {
        throw std::runtime_error(std::string(Paragraph::class_name()) + " - no value, handle: " +
                                 std::to_string(reinterpret_cast<size_t>(this)));
    }
    return val->getValue();
}

template<class Tracer>
bool Paragraph::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    tracer.trace(__FUNCTION__, " '", Paragraph::class_name(), "' - got: '", name, "'");
    this->create_from<XMLCreator>(name, reader, tracer);
    return true;
}

template<class Tracer>
void Paragraph::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Paragraph::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Paragraph::class_name() << ">\n";
}

#endif //FB2_PARAGRAPH_HPP
