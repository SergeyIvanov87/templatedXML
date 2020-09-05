#include <iostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "utils/Tracer.hpp"
#include "fb2/FictionBook.hpp"

enum eLogLevel : int
{
    ERROR_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL,
    TRACE_LEVEL
};

int main(int argc, char** argv)
{
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

        std::unique_ptr<xmlpp::TextReader> xml_reader = std::make_unique<xmlpp::TextReader>(xdxf_file_path);
        while(xml_reader->read())
        {
            std::string name = xml_reader->get_name();

            std::shared_ptr<FictionBook> art;
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art = XMLCreator::try_create<FictionBook>(name,
                                                          *xml_reader,
                                                          std_tracer);
            }
            else
            {
                art = XMLCreator::try_create<FictionBook>(name,
                                                          *xml_reader,
                                                          empty_tracer);
            }

            if (!art)
            {
                continue;
            }

            //Extract inner tags: `Body`
            auto body = art->get<Body>();
            if (body)
            {
                //Extract 'Section'
                auto section_container = body->get<XMLArrayContainerNode<Section>>();
                if (section_container)
                {
                    //Extract array of `Paragraph`s
                    const auto &array = section_container->getValue();
                    for (const auto& section : array)
                    {
                        const auto& paragraphs = section->get<XMLArrayContainerNode<Paragraph>>();
                        for (const auto & paragraph : paragraphs->getValue())
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
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
