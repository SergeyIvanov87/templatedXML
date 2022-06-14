#include <iostream>

#include <txml/txml.hpp>
#include <txml/applications/xdxf/xdxf.hpp>

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
    using namespace xdxf;

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
        while(xml_reader->read())
        {
            std::optional<XDXFArticle> art;
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art = XMLCreator::try_create<XDXFArticle>(*xml_reader,
                                                          std_tracer);
            }
            else
            {
                art = XMLCreator::try_create<XDXFArticle>(*xml_reader,
                                                          empty_tracer);
            }

            if (!art)
            {
                continue;
            }

            //Extract inner tags: KeyPhrase, Comment, Transcription and TextElement
            auto key_phrase = art->node<KeyPhrase>();
            auto comment = art->node<Comment>();
            auto transcr = art->node<Transcription>();
            auto text = art->node<TextElement>();

            //Printout
            if (key_phrase)
            {
                const std::string& name = key_phrase->value();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << KeyPhrase::class_name() << ": "<< name << std::endl;
                }
            }
            if (comment)
            {
                const std::string& name = comment->value();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << Comment::class_name() << ": "<< name << std::endl;
                }
            }
            if (transcr)
            {
                const std::string& name = transcr->value();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << Transcription::class_name() << ": "<< name << std::endl;
                }
            }
            if (text)
            {
                const std::string& name = text->value();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << TextElement::class_name() << ": "<< name << std::endl;
                }
            }

            //To stdout
            art->xml_serialize(std::cout);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
