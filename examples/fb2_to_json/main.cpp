#include <iostream>

#include <txml/applications/fb2/fb2.hpp>

#include "fb2_to_json.hpp"
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

        nlohmann::json data;
        Fb2ToJSON serializer(data);

        while(xml_reader->read())
        {
            std::shared_ptr<FictionBook> art;
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
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art->format_serialize(serializer, std_tracer);
                serializer.finalize(std_tracer);
            }
            else
            {
                art->format_serialize(serializer, empty_tracer);
                serializer.finalize(empty_tracer);
            }

            std::cout << "Dump serialized JSON:" << std::endl;
            std::cout << data.dump() << std::endl;

            // deserialize back to FB2
            Fb2FromJSON in(data);

            std::shared_ptr<FictionBook> deserialized_art;
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
            auto body = deserialized_art->getValue<Body>();
            if (body)
            {
                //Extract 'Section'
                const auto& section_container = body->getValue();
                for (const auto& section : section_container)
                {
                    const auto& paragraphs = section->getValue();
                    for (const auto & paragraph : paragraphs)
                    {
                        auto paragraph_val = paragraph->getValue();
                        if (log_level >= eLogLevel::DEBUG_LEVEL)
                        {
                            std_tracer << Paragraph::class_name() << ": "<< paragraph_val << std::endl;
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
