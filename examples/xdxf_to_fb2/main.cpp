#include <iostream>
#include <engine/TextReaderWrap.hpp>


#include <utils/Tracer.hpp>
#include <applications/xdxf/XDXFArticle.hpp>
#include <applications/xdxf/serializer/to_fb2.hpp>

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

        std::unique_ptr<TextReaderWrapper> xml_reader = std::make_unique<TextReaderWrapper>(xdxf_file_path);

        // Declare serializer object
        ToFB2<std::ostream> serializer(std::cout);

        // Print Header
        serializer.out << R"dict_header(<FictionBook xmlns="http://www.gribuser.ru/xml/fictionbook/2.0" xmlns:l="http://www.w3.org/1999/xlink">
<description></description>
<body>)dict_header" << std::endl;;
        while(xml_reader->read())
        {
            std::string name = xml_reader->get_name();

            std::shared_ptr<XDXFArticle> art;
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art = XMLCreator::try_create<XDXFArticle>(name,
                                                          *xml_reader,
                                                          std_tracer);
            }
            else
            {
                art = XMLCreator::try_create<XDXFArticle>(name,
                                                          *xml_reader,
                                                          empty_tracer);
            }

            if (!art)
            {
                continue;
            }


            //To Fb2 format
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art->format_serialize(serializer, std_tracer);
            }
            else
            {
                art->format_serialize(serializer, empty_tracer);
            }
        }

        // Print Footer
        serializer.out << R"dict_footer(
</body>"
</FictionBook>)dict_footer" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
