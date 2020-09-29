#ifndef FB2_SECTION_HPP
#define FB2_SECTION_HPP
#include <iostream>

#include "fb2/body/Section.h"
#include "fb2/common/Paragraph.hpp"
#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"
#include "XMLArrayContainerNode.hpp"


const char *Section::name() const noexcept
{
    return Section::class_name();
}

template<class Tracer>
void Section::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Section::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << Section::class_name() << ">\n";
}
#endif
