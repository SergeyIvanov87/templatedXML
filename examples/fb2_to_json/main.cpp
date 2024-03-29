#include <iostream>

#include <txml/applications/fb2/fb2.hpp>

#include "fb2_to_json.hpp"
#include "fb2_to_json_serializer_injection.hpp"
#include "json_to_fb2.hpp"

enum eLogLevel : int
{
    ERROR_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL,
    TRACE_LEVEL
};

int main(int argc, char** argv)
{
    using namespace txml;
    using namespace fb2;
    using namespace json;

    if (argc < 2)
    {
        perror("need file name");
        return -1;
    }

    eLogLevel log_level = eLogLevel::ERROR_LEVEL;
    if (argc > 2)
    {
        log_level = static_cast<eLogLevel>(std::max(std::atoi(argv[2]), static_cast<std::underlying_type_t<eLogLevel>>(eLogLevel::ERROR_LEVEL)));
    }
    std::string xdxf_file_path(argv[1]);
    std::locale::global(std::locale(""));
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        std::unique_ptr<TextReaderWrapper> xml_reader = std::make_unique<TextReaderWrapper>(xdxf_file_path);

        try
        {
            Fb2ToJSON serializer;

            while(xml_reader->read())
            {
                std::optional<FictionBook> art;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    art = XMLCreator::try_create<FictionBook>(*xml_reader,
                                                              std_tracer);
                }
                else
                {
                    art = XMLCreator::try_create<FictionBook>(*xml_reader,
                                                              empty_tracer);
                }

                if (!art)
                {
                    continue;
                }

                // To JSON format
                std::cout << "Begin serialize to JSON" << std::endl;
                nlohmann::json data;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    art->format_serialize(serializer, std_tracer);
                    data = serializer.finalize(std_tracer);
                }
                else
                {
                    art->format_serialize(serializer, empty_tracer);
                    data = serializer.finalize(empty_tracer);
                }

                std::cout << "Dump serialized JSON:" << std::endl;
                std::cout << data.dump() << std::endl;

                // deserialize back to FB2
                Fb2FromJSON in(data);

                std::optional<FictionBook> deserialized_art;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    deserialized_art = FictionBook::format_deserialize(in, std_tracer);
                }
                else
                {
                    deserialized_art = FictionBook::format_deserialize(in, empty_tracer);
                }

                if (!deserialized_art)
                {
                    std::cerr << "Cannot deserialize FictionBook" << std::endl;
                    return -1;
                }

                //Extract inner tags: `Body`
                const auto &body = deserialized_art->node<Body>();
                if (body)
                {
                    //Extract 'Section'
                    const auto& section_container = body->value();
                    for (const auto& section : section_container)
                    {
                        const auto& paragraphs = section->value();
                        for (const auto & paragraph : paragraphs)
                        {
                            const auto &paragraph_val = paragraph->value();
                            if (log_level >= eLogLevel::DEBUG_LEVEL)
                            {
                                std_tracer << Paragraph::class_name() << ": "<< paragraph_val << std::endl;
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception &ex)
        {
            throw;
        }

        //
        xml_reader = std::make_unique<TextReaderWrapper>(xdxf_file_path);
        try
        {
            ToInjectedSerializer serializer;

            while(xml_reader->read())
            {
                std::optional<FictionBook> art;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    art = XMLCreator::try_create<FictionBook>(*xml_reader,
                                                              std_tracer);
                }
                else
                {
                    art = XMLCreator::try_create<FictionBook>(*xml_reader,
                                                              empty_tracer);
                }

                if (!art)
                {
                    continue;
                }

                // To JSON format
                std::cout << "Begin serialize to JSON" << std::endl;
                nlohmann::json data;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    art->format_serialize(serializer, std_tracer);
                    data = serializer.finalize(std_tracer);
                }
                else
                {
                    art->format_serialize(serializer, empty_tracer);
                    data = serializer.finalize(empty_tracer);
                }

                std::cout << "Dump serialized JSON:" << std::endl;
                std::cout << data.dump() << std::endl;

                // deserialize back to FB2
                Fb2FromJSON in(data);

                std::optional<FictionBook> deserialized_art;
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    deserialized_art = FictionBook::format_deserialize(in, std_tracer);
                }
                else
                {
                    deserialized_art = FictionBook::format_deserialize(in, empty_tracer);
                }

                if (!deserialized_art)
                {
                    std::cerr << "Cannot deserialize FictionBook" << std::endl;
                    return -1;
                }

                //Extract inner tags: `Body`
                const auto &body = deserialized_art->node<Body>();
                if (body)
                {
                    //Extract 'Section'
                    const auto& section_container = body->value();
                    for (const auto& section : section_container)
                    {
                        const auto& paragraphs = section->value();
                        for (const auto & paragraph : paragraphs)
                        {
                            const auto &paragraph_val = paragraph->value();
                            if (log_level >= eLogLevel::DEBUG_LEVEL)
                            {
                                std_tracer << Paragraph::class_name() << ": "<< paragraph_val << std::endl;
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception &ex)
        {
            throw;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
