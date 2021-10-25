#ifndef JSON_TO_FB2_DESERIALIZER_HPP
#define JSON_TO_FB2_DESERIALIZER_HPP

#include <stack>

#include <txml/include/utils/Deserializer.hpp>
#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
#if 0
struct Fb2FromJSON : public txml::FormatDeserializerBase<Fb2FromJSON, txml::StaticCheckUnscopedElement,
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
    Fb2FromJSON(json &obj) :
        in(obj)
    {
        iterators_stack.emplace(in.begin(), in.end());
    }


    template<class Tracer>
    std::shared_ptr<FictionBook> deserialize_impl(txml::details::SchemaDTag<FictionBook>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<FictionBook>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<FictionBook>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Description> deserialize_impl(txml::details::SchemaDTag<Description>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<Description>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Description>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<TitleInfo> deserialize_impl(txml::details::SchemaDTag<TitleInfo>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<TitleInfo>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<TitleInfo>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<BookTitle> deserialize_impl(txml::details::SchemaDTag<BookTitle>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<BookTitle>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<BookTitle>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

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
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<DocumentInfo>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<DocumentInfo>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

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
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_node_param<PublishInfo>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<PublishInfo>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Body> deserialize_impl(txml::details::SchemaDTag<Body>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Body>(begin_it, end_it, json::value_t::array, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Body>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Section> deserialize_impl(txml::details::SchemaDTag<Section>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Section>(begin_it, end_it, json::value_t::array, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Section>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Paragraph>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Paragraph>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Binary> deserialize_impl(txml::details::SchemaDTag<Binary>, Tracer tracer)
    {
        return {};
    }

private:
    json &in;

    using begin_iterator_t = json::iterator;
    using end_iterator_t = json::iterator;
    using range_iterator = std::pair<begin_iterator_t, end_iterator_t>;
    std::stack<range_iterator> iterators_stack;

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
            tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(expected_type));
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
            tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(expected_type));
            return false;
        }
        return true;
    }

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer, size_t available_item_count)
    {
        std::shared_ptr<NodeType> ret = std::make_shared<NodeType>();
        tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                     ret.get());

        size_t deserialized_item_count = ret->format_deserialize_elements(*this, tracer);
        while (deserialized_item_count != available_item_count)
        {
            tracer.trace("refill node '", NodeType::class_name(), "' handle: ",
                     ret.get(), " deserialized count: ", deserialized_item_count);
            size_t next_portion_items = ret->format_deserialize_elements(*this, tracer);
            if (deserialized_item_count == next_portion_items)
            {
                break; //nothing more
            }
            deserialized_item_count = next_portion_items;
        }
        return ret;
    }
};
#endif


struct Fb2FromJSON : public json::FromJSON<Fb2FromJSON,
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

    using FromJSON<Fb2FromJSON,
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
                                                        Binary>::deserialize_impl;
    template<class Tracer>
    std::shared_ptr<FB2TextElement> deserialize_impl(txml::details::SchemaDTag<FB2TextElement>, Tracer tracer)
    {
        return {};
    }

    template<class Tracer>
    std::shared_ptr<Empty> deserialize_impl(txml::details::SchemaDTag<Empty>, Tracer tracer)
    {
        return {};
    }

    template<class Tracer>
    std::shared_ptr<Body> deserialize_impl(txml::details::SchemaDTag<Body>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Body>(begin_it, end_it, json::value_t::array, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Body>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Section> deserialize_impl(txml::details::SchemaDTag<Section>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Section>(begin_it, end_it, json::value_t::array, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Section>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        auto& [begin_it, end_it] = iterators_stack.top();
        if (!check_array_node_param<Paragraph>(begin_it, end_it, json::value_t::object, tracer))
        {
            return {};
        }

        iterators_stack.emplace(begin_it.value().begin(), begin_it.value().end());
        auto ret = create_deserialized_node<Paragraph>(tracer, std::distance(begin_it.value().begin(), begin_it.value().end()));
        iterators_stack.pop();
        ++begin_it;

        return ret;
    }

    template<class Tracer>
    std::shared_ptr<Binary> deserialize_impl(txml::details::SchemaDTag<Binary>, Tracer tracer)
    {
        return {};
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
            tracer.trace("Expected '", NodeType::class_name(), "', type: ", json_type_to_cstring(expected_type));
            return false;
        }
        return true;
    }

};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
