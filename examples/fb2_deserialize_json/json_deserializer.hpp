#ifndef JSON_TO_FB2_DESERIALIZER_HPP
#define JSON_TO_FB2_DESERIALIZER_HPP

#include <nlohmann/json.hpp>

#include <txml/include/utils/Deserializer.hpp>
#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{

struct FromJSON : public txml::FormatDeserializerBase<FromJSON, txml::StaticCheckUnscopedElement,
                                                    FictionBook,
                                                        Description,
                                                            TitleInfo,
                                                                BookTitle,
                                                                    FB2TextElement,
                                                            DocumentInfo,
                                                                Empty,
                                                            PublishInfo,
                                                                //Empty,
                                                        Body,
                                                            Section,
                                                                Paragraph,
                                                        Binary>
{
    using json = nlohmann::json;
    FromJSON(json &obj) :
        in(obj)
    {
        it = in.begin();
        it_end = in.end();
    }


    static const char* json_type_to_cstring(json::value_t type)
    {
        switch(type)
        {
            case json::value_t::null:
                return "'null'";
            case json::value_t::boolean:
                return "'boolean'";
            case json::value_t::string:
                return "'string'";
            case json::value_t::number_integer:
                return "'number (integer)'";
            case json::value_t::number_unsigned:
                return "'number (unsigned integer)'";
            case json::value_t::number_float:
                return "'number (floating-point)'";
            case json::value_t::object:
                return "'object'";
            case json::value_t::array:
                return "'array'";
            case json::value_t::discarded:
                return "'discarded'";
            default:
                return "<unknown>";
        }
    }

    template<class Tracer>
    std::shared_ptr<FictionBook> deserialize_impl(txml::details::SchemaDTag<FictionBook>, Tracer tracer)
    {
        if (!check_node_param<FictionBook>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<FictionBook>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Description> deserialize_impl(txml::details::SchemaDTag<Description>, Tracer tracer)
    {
        if (!check_node_param<Description>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<Description>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<TitleInfo> deserialize_impl(txml::details::SchemaDTag<TitleInfo>, Tracer tracer)
    {
        if (!check_node_param<TitleInfo>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<TitleInfo>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<BookTitle> deserialize_impl(txml::details::SchemaDTag<BookTitle>, Tracer tracer)
    {
        if (!check_node_param<BookTitle>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<BookTitle>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<FB2TextElement> deserialize_impl(txml::details::SchemaDTag<FB2TextElement>, Tracer tracer)
    {
        return {};
    }

    template<class Tracer>
    std::shared_ptr<DocumentInfo> deserialize_impl(txml::details::SchemaDTag<DocumentInfo>, Tracer tracer)
    {
        if (!check_node_param<DocumentInfo>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<DocumentInfo>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Empty> deserialize_impl(txml::details::SchemaDTag<Empty>, Tracer tracer)
    {
        return {};
    }

    template<class Tracer>
    std::shared_ptr<PublishInfo> deserialize_impl(txml::details::SchemaDTag<PublishInfo>, Tracer tracer)
    {
        if (!check_node_param<PublishInfo>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<PublishInfo>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Body> deserialize_impl(txml::details::SchemaDTag<Body>, Tracer tracer)
    {
        if (!check_array_node_param<Body>(it, it_end, json::value_t::array, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<Body>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Section> deserialize_impl(txml::details::SchemaDTag<Section>, Tracer tracer)
    {
        if (!check_array_node_param<Section>(it, it_end, json::value_t::array, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<Section>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        if (!check_array_node_param<Paragraph>(it, it_end, json::value_t::object, tracer))
        {
            return {};
        }

        auto stored_it = it;
        auto stored_it_end = it_end;

        it = stored_it.value().begin();
        it_end = stored_it.value().end();

        auto ret = create_deserialized_node<Paragraph>(tracer);

        it = ++stored_it;
        it_end = stored_it_end;
        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Binary> deserialize_impl(txml::details::SchemaDTag<Binary>, Tracer tracer)
    {
        return {};
    }

private:
    json &in;
    json::iterator it;
    json::iterator it_end;


    template<class NodeType, class Tracer>
    static bool check_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                 json::value_t expected_type, Tracer tracer)
    {
        if (cur_it == cur_end_it)
        {
            tracer.trace("EOF");
            return false;
        }

        const std::string &key = cur_it.key();
        const auto& value = cur_it.value();

        tracer.trace("Found '", key, "', value type: ", json_type_to_cstring(value.type()), ", value:\n", value);
        if (value.type() != expected_type || key != NodeType::class_name())
        {
            tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(json::value_t::object));
            return false;
        }
        return true;
    }

    template<class NodeType, class Tracer>
    static bool check_array_node_param(json::iterator& cur_it, const json::iterator& cur_end_it,
                                       json::value_t expected_type, Tracer tracer)
    {
        if (cur_it == cur_end_it)
        {
            tracer.trace("EOF");
            return false;
        }

        const auto& value = cur_it.value();

        tracer.trace("Found: array element, value type: ", json_type_to_cstring(value.type()), ", value:\n", value);
        if (value.type() != expected_type)
        {
            tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(json::value_t::object));
            return false;
        }
        return true;
    }

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer)
    {
        std::shared_ptr<NodeType> ret = std::make_shared<NodeType>();
        tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                     ret.get());

        ret->format_deserialize_elements(*this, tracer);
        return ret;
    }
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
