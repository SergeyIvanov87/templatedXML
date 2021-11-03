#ifndef JSON_TO_FB2_DESERIALIZER_HPP
#define JSON_TO_FB2_DESERIALIZER_HPP

#include <stack>

#include <txml/txml_fwd.h>
#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{
/*
#define DESERIALIZED_TYPES  FictionBook,                                    \
                                        Description,                        \
                                                TitleInfo,                  \
                                                    BookTitle,              \
                                                        FB2TextElement,     \
                                                DocumentInfo,               \
                                                    Empty,                  \
                                                PublishInfo,                \
                                                    /*Empty,* /              \
                                                Body,                       \
                                                    Section,                \
                                                        Paragraph,          \
                                                Binary

struct Fb2FromJSON : public json::FromJSON<Fb2FromJSON, DESERIALIZED_TYPES>
{
    using json = nlohmann::json;
    using FromJSON<Fb2FromJSON, DESERIALIZED_TYPES>::deserialize_impl;

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
};
#undef DESERIALIZED_TYPES
*/
using namespace json;
TXML_DECLARE_DESERIALIZER_CLASS(Fb2FromJSON, FromJSON,
                                                    FictionBook,
                                                        Description,
                                                            TitleInfo,
                                                                BookTitle,
                                                                    FB2TextElement,
                                                            DocumentInfo,
                                                                Empty,
                                                            PublishInfo,
                                                            Body,
                                                                Section,
                                                                    Paragraph,
                                                                    Binary)
{
    TXML_DESERIALIZER_OBJECT
    using json = nlohmann::json;
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
};


} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
