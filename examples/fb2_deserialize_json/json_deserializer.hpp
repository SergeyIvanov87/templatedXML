#ifndef JSON_TO_FB2_DESERIALIZER_HPP
#define JSON_TO_FB2_DESERIALIZER_HPP

#include <stack>

#include <txml/applications/fb2/fb2.hpp>
#include <txml/applications/json/json.hpp>

namespace fb2
{

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
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
