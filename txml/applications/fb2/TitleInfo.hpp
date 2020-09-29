#ifndef FB2_TITLE_INFO_HPP
#define FB2_TITLE_INFO_HPP
#include <iostream>

#include "fb2/TitleInfo.h"
#include "fb2/BookTitle.hpp"

#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *TitleInfo::name() const noexcept
{
    return TitleInfo::class_name();
}

template<class Tracer>
void TitleInfo::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << TitleInfo::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << TitleInfo::class_name() << ">\n";
}
#endif
