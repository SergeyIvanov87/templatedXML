#ifndef FB2_PARAGRAPH_HPP
#define FB2_PARAGRAPH_HPP
#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/applications/fb2/common/Paragraph.h>
#include <txml/applications/fb2/FB2TextElement.hpp>

namespace fb2
{
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
void Paragraph::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Paragraph::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << Paragraph::class_name() << ">\n";
}
} // namespace fb2
#endif //FB2_PARAGRAPH_HPP
