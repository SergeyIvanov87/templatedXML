#ifndef XDXF_ARTICLE_HPP
#define XDXF_ARTICLE_HPP
#include <iostream>

#include "xdxf/XDXFArticle.h"
#include "xdxf/KeyPhrase.hpp"
#include "xdxf/Comment.hpp"
#include "xdxf/Transcription.hpp"
#include "xdxf/TextElement.hpp"
#include "XMLProducible.hpp"
#include "XMLSerializable.hpp"
#include "XMLCreator.hpp"
#include "XMLNode.hpp"

const char *XDXFArticle::name() const noexcept
{
    return XDXFArticle::class_name();
}

template<class Tracer>
bool XDXFArticle::initialize(std::string &name, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, reader, tracer);
    return true;
}

template<class Tracer>
void XDXFArticle::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << XDXFArticle::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << XDXFArticle::class_name() << ">\n";
}


template<class Formatter, class Tracer = EmptyTracer>
void XDXFArticle::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}
#endif
