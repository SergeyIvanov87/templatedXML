#ifndef XDXF_ARTICLE_HPP
#define XDXF_ARTICLE_HPP

#include <iostream>

#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLNode.hpp>

#include <txml/applications/xdxf/include/fwd/XDXFArticle.h>
#include <txml/applications/xdxf/include/KeyPhrase.hpp>
#include <txml/applications/xdxf/include/Comment.hpp>
#include <txml/applications/xdxf/include/Transcription.hpp>
#include <txml/applications/xdxf/include/TextElement.hpp>

namespace xdxf
{
const char *XDXFArticle::name() const noexcept
{
    return XDXFArticle::class_name();
}

template<class Tracer>
void XDXFArticle::serialize_impl(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << XDXFArticle::class_name() << ">";
    this->serialize_elements(out, tracer, txml::no_sep);
    out << "</" << XDXFArticle::class_name() << ">\n";
}


template<class Formatter, class Tracer>
void XDXFArticle::format_serialize_impl(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}

template<class Formatter, class Tracer>
void XDXFArticle::schema_serialize_impl(Formatter& out, Tracer tracer)
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.template map<XDXFArticle>(tracer);
}
} // namespace xdxf
#endif
