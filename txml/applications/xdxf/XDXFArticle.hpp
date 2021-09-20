#ifndef XDXF_ARTICLE_HPP
#define XDXF_ARTICLE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/xdxf/XDXFArticle.h>
#include <txml/applications/xdxf/KeyPhrase.hpp>
#include <txml/applications/xdxf/Comment.hpp>
#include <txml/applications/xdxf/Transcription.hpp>
#include <txml/applications/xdxf/TextElement.hpp>

const char *XDXFArticle::name() const noexcept
{
    return XDXFArticle::class_name();
}

template<class Tracer>
void XDXFArticle::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << XDXFArticle::class_name() << ">";
    this->serialize_elements(out, tracer, no_sep);
    out << "</" << XDXFArticle::class_name() << ">\n";
}


template<class Formatter, class Tracer>
void XDXFArticle::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}
#endif
