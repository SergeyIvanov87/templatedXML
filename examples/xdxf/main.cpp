#include <iostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include <utils/Tracer.hpp>
#include <applications/xdxf/XDXFArticle.hpp>

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

            //Extract inner tags: KeyPhrase, Comment, Transcription and TextElement
            auto key_phrase = art->get<KeyPhrase>();
            auto comment = art->get<Comment>();
            auto transcr = art->get<Transcription>();
            auto text = art->get<TextElement>();

            //Printout
            if (key_phrase)
            {
                const std::string& name = key_phrase->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << KeyPhrase::class_name() << ": "<< name << std::endl;
                }
            }
            if (comment)
            {
                const std::string& name = comment->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << Comment::class_name() << ": "<< name << std::endl;
                }
            }
            if (transcr)
            {
                const std::string& name = transcr->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << Transcription::class_name() << ": "<< name << std::endl;
                }
            }
            if (text)
            {
                const std::string& name = text->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << TextElement::class_name() << ": "<< name << std::endl;
                }
            }

            //To stdout
            art->serialize(std::cout);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
