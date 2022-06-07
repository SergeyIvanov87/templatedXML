#include <iostream>

#include <txml/applications/fb2/fb2.hpp>

#include "xml_deserializer.hpp"

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

        TextReaderWrapper xml_reader(xdxf_file_path);
        Fb2FromXML in(xml_reader);

        std::optional<FictionBook> art;
        do {
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art = FictionBook::format_deserialize(in, std_tracer);
            }
            else
            {
                art = FictionBook::format_deserialize(in, empty_tracer);
            }
        }
        while (!art);

        if (!art)
        {
            std::cerr << "Cannot deserialize FictionBook" << std::endl;
            return -1;
        }

        //Extract inner tags: `Body`
        auto body = art->node<Body>();
        if (body)
        {
            //Extract 'Section'
            const auto& section_container = body->value();
            for (const auto& section : section_container)
            {
                const auto& paragraphs = section->value();
                for (const auto & paragraph : paragraphs)
                {
                    auto paragraph_val = paragraph->value();
                    if (log_level >= eLogLevel::DEBUG_LEVEL)
                    {
                        std_tracer << Paragraph::class_name() << ": "<< paragraph_val << std::endl;
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
