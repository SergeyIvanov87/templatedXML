#ifndef XML_TO_FB2_DESERIALIZER_HPP
#define XML_TO_FB2_DESERIALIZER_HPP

#include <txml/include/utils/Deserializer.hpp>
#include <txml/include/engine/TextReaderWrap.hpp>
#include <txml/applications/fb2/fb2.hpp>

namespace fb2
{

template<class NodeType, class Tracer>
bool check_node_param(const txml::TextReaderWrapper &reader, Tracer tracer)
{
    const std::string &name = reader.get_name();
    txml::TextReaderWrapper::NodeType nodeType = reader.get_node_type();
    auto depth = reader.get_depth();
    tracer.trace("Found '", to_string(nodeType), "', tag name: '", name,
                 "', depth: ", depth);
    if (name != NodeType::class_name() || nodeType != NodeType::class_node_type())
    {

        tracer.trace("Expected '", to_string(NodeType::class_node_type()), "', tag name: '", NodeType::class_name(), "'");
        return false;
    }
    return true;
}

struct FromXML : public txml::FormatDeserializerBase<FromXML, txml::StaticCheckUnscopedElement,
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
    FromXML(txml::TextReaderWrapper &stream) :
        in(stream)
    {
    }


    template<class Tracer>
    std::shared_ptr<FictionBook> deserialize_impl(txml::details::SchemaDTag<FictionBook>, Tracer tracer)
    {
        if (!in.read() || !check_node_param<FictionBook> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<FictionBook>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Description> deserialize_impl(txml::details::SchemaDTag<Description>, Tracer tracer)
    {
        if (!check_node_param<Description> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<Description>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<TitleInfo> deserialize_impl(txml::details::SchemaDTag<TitleInfo>, Tracer tracer)
    {
        if (!check_node_param<TitleInfo> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<TitleInfo>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<BookTitle> deserialize_impl(txml::details::SchemaDTag<BookTitle>, Tracer tracer)
    {
        if (!check_node_param<BookTitle> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<BookTitle>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<FB2TextElement> deserialize_impl(txml::details::SchemaDTag<FB2TextElement>, Tracer tracer)
    {
        return std::shared_ptr<FB2TextElement>{};
    }

    template<class Tracer>
    std::shared_ptr<DocumentInfo> deserialize_impl(txml::details::SchemaDTag<DocumentInfo>, Tracer tracer)
    {
        if (!check_node_param<DocumentInfo> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<DocumentInfo>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Empty> deserialize_impl(txml::details::SchemaDTag<Empty>, Tracer tracer)
    {
        return std::shared_ptr<Empty>{};
    }

    template<class Tracer>
    std::shared_ptr<PublishInfo> deserialize_impl(txml::details::SchemaDTag<PublishInfo>, Tracer tracer)
    {
        if (!check_node_param<PublishInfo> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<PublishInfo>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Body> deserialize_impl(txml::details::SchemaDTag<Body>, Tracer tracer)
    {
        if (!check_node_param<Body> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<Body>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Section> deserialize_impl(txml::details::SchemaDTag<Section>, Tracer tracer)
    {
        if (!check_node_param<Section> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<Section>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Paragraph> deserialize_impl(txml::details::SchemaDTag<Paragraph>, Tracer tracer)
    {
        if (!check_node_param<Paragraph> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<Paragraph>(tracer);
    }

    template<class Tracer>
    std::shared_ptr<Binary> deserialize_impl(txml::details::SchemaDTag<Binary>, Tracer tracer)
    {
        if (!check_node_param<Binary> (in, tracer)) {
            return {};
        }

        return create_deserialized_node<Binary>(tracer);
    }

    txml::TextReaderWrapper &in;

private:

    template<class NodeType, class Tracer>
    std::shared_ptr<NodeType> create_deserialized_node(Tracer tracer)
    {
        int node_depth = in.get_depth();

        std::shared_ptr<NodeType> ret = std::make_shared<NodeType>();
        tracer.trace("Create node '", NodeType::class_name(), "' handle: ",
                     ret.get(),
                     ", depth: ", node_depth);

        bool get_next = false;
        Tracer node_tracer = tracer;
        while (in.read())
        {
            node_tracer.trace("Open node '", to_string(in.get_node_type()),
                         "', tag name: '", in.get_name(),
                         "', depth: ", in.get_depth());
            if (in.get_name() == NodeType::class_name() &&
                in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
                node_depth == in.get_depth())
            {
                tracer.trace("Close node '", to_string(NodeType::class_node_type()),
                             "', tag name: '",  NodeType::class_name(),
                             "' handle: ", ret.get(),
                             "', depth: ", node_depth);
                in.read();
                break;
            }
            bool node_processed = ret->format_deserialize_elements(*this, tracer);
            get_next |= node_processed;

            if (!node_processed && in.get_node_type() == txml::TextReaderWrapper::NodeType::Element)
            {
                const std::string& unprocessed_name = in.get_name();
                int depth = in.get_depth();
                node_tracer.trace("Skipping node: ", unprocessed_name, ", type: ",
                                  to_string(in.get_node_type()), ", depth: ", depth);
                Tracer sub_tracer = node_tracer;
                while (in.read())
                {
                    if ((in.get_name() == unprocessed_name &&
                        in.get_node_type() == txml::TextReaderWrapper::NodeType::EndElement &&
                        in.get_depth() == depth)

                        ||

                        in.get_depth() <= depth
                        )
                    {
                        break;
                    }
                    else
                    {
                        sub_tracer.trace("To skip node: ", in.get_name(), ", type: ",
                                         to_string(in.get_node_type()), ", depth: ", in.get_depth());
                    }
                }
                node_tracer.trace("Skipped node: ", unprocessed_name, ", depth: ", depth);
            }
        }
        tracer.trace("Return node '", NodeType::class_name(), "' handle: ", ret.get());
        return ret;
    }
};
} // namespace fb2
#endif //FB2_TO_SCHEMA_SERIALIZER_HPP
