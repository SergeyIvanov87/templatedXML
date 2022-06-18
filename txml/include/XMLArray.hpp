#ifndef XML_ARRAY_HPP
#define XML_ARRAY_HPP

#include <txml/include/fwd/XMLArray.h>

#include <txml/include/XMLProducible.hpp>
#include <txml/include/XMLCreator.hpp>
#include <txml/include/XMLSerializable.hpp>
#include <txml/include/XMLDeserializable.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/include/engine/TracerHelper.hpp>

namespace txml
{
#define TEMPL_ARGS_DECL    class Impl, class ElementType
#define TEMPL_ARGS_DEF     Impl, ElementType

template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF>::XMLArray(NodesStorage &&val) :
    storage(std::move(val))
{
}

template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF>::XMLArray(const NodesStorage &val) :
    storage(val)
{
}
template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF>::XMLArray(std::initializer_list<ChildNode> list) :
    storage(list)
{
}

template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF>::XMLArray(XMLArray &&src) :
    TracerHelper<Impl>(static_cast<TracerHelper<Impl>&&>(src)),
    storage(std::move(src.storage))
{
}

template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF>::XMLArray(const XMLArray &src) :
    TracerHelper<Impl>(src),
    storage(src.storage)
{
}
template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF> &XMLArray<TEMPL_ARGS_DEF>::operator=(const XMLArray &src)
{
    if (this != &src)
    {
        storage = src.storage;
        static_cast<TracerHelper<Impl>&>(*this) = static_cast<const TracerHelper<Impl>&>(src);
    }
    return *this;
}

template<TEMPL_ARGS_DECL>
XMLArray<TEMPL_ARGS_DEF> &XMLArray<TEMPL_ARGS_DEF>::operator=(XMLArray &&src)
{
    if (this != &src)
    {
        storage = std::move(src.storage);
        static_cast<TracerHelper<Impl>&>(*this) = static_cast<TracerHelper<Impl>&&>(src);
    }
    return *this;
}


template<TEMPL_ARGS_DECL>
template<class Fabric, class ...CreationArgs>
size_t XMLArray<TEMPL_ARGS_DEF>::create_from(CreationArgs&&... next_args)
{
    std::optional<ElementType> elem;
    do {
        elem = Fabric::template try_create<ElementType>(std::forward<CreationArgs>(next_args)...);
        if (elem) {
            storage.push_back(elem);
        }
    } while (elem);
    return storage.size();
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
bool XMLArray<TEMPL_ARGS_DEF>::initialize(TextReaderWrapper &reader, Tracer tracer/* = Tracer()*/)
{
    const std::string &name = reader.get_name();
    tracer.trace("try saturate array '", Impl::class_name(), "' by '", name, "'");
    size_t ret = this->template create_from<XMLCreator>(reader, tracer);
    tracer.trace("saturation array '", Impl::class_name(), "' with: '", name, "', got count: ", ret);
    return ret;
}

template<TEMPL_ARGS_DECL>
const typename XMLArray<TEMPL_ARGS_DEF>::NodesStorage &XMLArray<TEMPL_ARGS_DEF>::value() const
{
    return storage;
}

template<TEMPL_ARGS_DECL>
typename XMLArray<TEMPL_ARGS_DEF>::NodesStorage &XMLArray<TEMPL_ARGS_DEF>::value()
{
    return storage;
}

template<TEMPL_ARGS_DECL>
template<class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::make_xml_serialize(std::ostream &out, Tracer tracer/* = Tracer()*/) const
{
    out << "<" << Impl::class_name() << ">";
    for (const auto& elem : storage)
    {
        if (elem)
        {
            elem->xml_serialize(out, tracer);
        }
    }
    out << "</" << Impl::class_name() << ">\n";
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::make_format_serialize(Formatter &out, Tracer tracer) const
{
    tracer.trace("'", Impl::class_name(), "' ", *static_cast<const Impl*>(this)," - ", __FUNCTION__, " - START, size: ", storage.size());
    size_t i = 0, count = 0;
    for (const auto& elem : storage)
    {
        tracer.trace("'", Impl::class_name(), "' ", *static_cast<const Impl*>(this)," - ", __FUNCTION__, " - BEGIN element index: ", i);
        if (elem)
        {
            elem->format_serialize(out, tracer);
            count ++;
        }
        tracer.trace("'", Impl::class_name(), "' ", *static_cast<const Impl*>(this)," - ", __FUNCTION__, " - END element index: ", i);
        i++;
    }
    tracer.trace("'", Impl::class_name(), "' ", *static_cast<const Impl*>(this)," - ", __FUNCTION__, " - FINISH, count: (", count, "/", storage.size(), ")");
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::make_schema_serialize(Formatter &out, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - START");
    ElementType::schema_serialize(out, tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - FINISH");
}



template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
size_t XMLArray<TEMPL_ARGS_DEF>::make_format_deserialize(Formatter &in, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - START");

    std::optional<ElementType> elem;

    size_t deserialized_count = 0;
    do {
        size_t array_index = storage.size();
        tracer.trace("Begin array index: ", array_index);
        elem = ElementType::format_deserialize(in, tracer);
        if (elem) {
            storage.push_back(elem);
            deserialized_count++;
        }
        tracer.trace("End array index: ", array_index);
    } while (elem);

    tracer.trace("'", Impl::class_name(), "' ", *static_cast<Impl*>(this)," - ", __FUNCTION__, " - FINISH, deserialized count: ", deserialized_count);
    return deserialized_count;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::format_serialize_request(Formatter& out, Tracer tracer) const
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    out.map(static_cast<const Impl&>(*this), tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - ACK: ", static_cast<const Impl&>(*this));
}


template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
std::optional<Impl> XMLArray<TEMPL_ARGS_DEF>::format_deserialize_request(Formatter& in, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    auto ret = in.template map<Impl>(tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, ret ? " - ACK: " : " - NACK: ", ret);
    return ret;
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::format_redeserialize_request(Formatter& in, Tracer tracer)
{
}

template<TEMPL_ARGS_DECL>
template<class Formatter, class Tracer>
void XMLArray<TEMPL_ARGS_DEF>::schema_serialize_request(Formatter& out, Tracer tracer)
{
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - PERFORM");
    out.template map<Impl>(tracer);
    tracer.trace("'", Impl::class_name(), "' - ", __FUNCTION__, " - ACK");
}

#undef TEMPL_ARGS_DEF
#undef TEMPL_ARGS_DECL
} // namespace txml
#endif //XML_ARRAY_HPP
