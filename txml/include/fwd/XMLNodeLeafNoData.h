#ifndef XML_NODE_LEAF_NO_DATA_H
#define XML_NODE_LEAF_NO_DATA_H

#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include <txml/include/engine/fwd/TextReaderWrap.h>
#include <txml/include/utils/fwd/utils.h>
#include <txml/include/utils/fwd/specific_tracer/EmptyTracer.h>

#include <txml/include/fwd/XMLSerializable.h>
#include <txml/include/fwd/XMLDeserializable.h>
#include <txml/include/engine/fwd/TagHolder.h>
#include <txml/include/details/fwd/Searchable.h>
#include <txml/include/engine/fwd/TracerHelper.h>

namespace txml
{
template<class Impl>
struct XMLNodeLeafNoData : public XMLFormatSerializable<Impl>,
                     public XMLFormatDeserializable<Impl>,
                     public XMLSchemaSerializable<Impl>,
                     public Searchable<Impl>,
                     public TagHolder<NoDataTag>,
                     public TracerHelper<Impl>

{
    friend class XMLFormatSerializable<Impl>;
    friend class XMLFormatDeserializable<Impl>;
    friend class XMLSchemaSerializable<Impl>;

    using tags_t = TagHolder<NoDataTag>;
    using modifiers_t = std::optional<std::vector<std::string>>;

    XMLNodeLeafNoData() = default;

    template<class Tracer = EmptyTracer>
    static std::optional<Impl> create(TextReaderWrapper &reader, Tracer tracer);

    template<class Tracer = EmptyTracer>
    void fill_impl(TextReaderWrapper &reader, Tracer tracer);

protected:
    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_serialize_request(Formatter& out, Tracer tracer = Tracer()) const;

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static std::optional<Impl> format_deserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    void format_redeserialize_request(Formatter& in, Tracer tracer = Tracer());

    template<class Formatter, class Tracer = txml::EmptyTracer>
    static void schema_serialize_request(Formatter& out, Tracer tracer = Tracer());
};
} // namespace txml
#endif //XML_NODE_LEAF_NO_DATA_H
