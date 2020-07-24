#ifndef XDXF_ARTICLE_HPP
#define XDXF_ARTICLE_HPP
#include <iostream>

#include "common/xdxf/XDXFArticle.h"
#include "common/xdxf/KeyPhrase.hpp"
#include "common/xdxf/Comment.hpp"
#include "common/xdxf/Transcription.hpp"
#include "common/xdxf/TextElement.hpp"
#include "common/xml/XMLProducible.hpp"
#include "common/xml/XMLPublishing.hpp"
#include "common/xml/XMLCreator.hpp"
#include "common/xml/XMLNode.hpp"

const char *XDXFArticle::name() const noexcept
{
    return XDXFArticle::class_name();
}

template<class Tracer>
bool XDXFArticle::initialize(std::string &name, int &depth, xmlpp::TextReader &reader, Tracer tracer/* = Tracer()*/)
{
    this->create_from<XMLCreator>(name, depth, reader, tracer);
    return true;
}

template<class Tracer>
void XDXFArticle::dump(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << XDXFArticle::class_name() << ">";
    this->dump_all(out, tracer, no_sep);
    out << "</" << XDXFArticle::class_name() << ">\n";
}


template<class Formatter, class Tracer = Tracer<EmptyTracerImpl>>
void XDXFArticle::format_dump(Formatter& out, Tracer tracer) const
{
    tracer.trace(__FUNCTION__, " - ", class_name());
    out.map(*this, tracer);
}
#endif
