#include <iostream>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "utils/Tracer.hpp"
#include "xdxf/XDXFArticle.hpp"
enum eLogLevel : int
{
    ERROR_LEVEL,
    INFO_LEVEL,
    DEBUG_LEVEL,
    TRACE_LEVEL
};

struct indent {
  int depth_;
  explicit indent(int depth): depth_(depth) {};
};

std::ostream & operator<<(std::ostream & o, indent const & in)
{
  for(int i = 0; i != in.depth_; ++i)
  {
    o << "  ";
  }
  return o;
}

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
        log_level = static_cast<eLogLevel>(std::max(std::atoi(argv[2]), static_cast<std::underlying_type_t<eLogLevel>>(eLogLevel::ERROR_LEVEL));
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

            int depth = xml_reader->get_depth();
            std::shared_ptr<XDXFArticle> art;
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                art = XMLCreator::try_create<XDXFArticle>(xml_reader->get_name(),
                                                          xml_reader->get_depth(),
                                                          *xml_reader,
                                                          std_tracer);
            }
            else
            {
                art = XMLCreator::try_create<XDXFArticle>(xml_reader->get_name(),
                                                          xml_reader->get_depth(),
                                                          *xml_reader,
                                                          empty_tracer);
            }

            if (!art)
            {
                continue;
            }

            //Extract KeyPhrase
            auto key_phrase = art->get<KeyPhrase>();
            if (key_phrase)
            {
                const std::string& name = key_phrase->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << indent(depth) << KeyPhrase::class_name() << ": "<< name << std::endl;
                }
            }

            //Extract Comment
            auto comment = art->get<Comment>();
            if (comment)
            {
                const std::string& name = comment->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << indent(depth) << Comment::class_name() << ": "<< name << std::endl;
                }
            }

            //Extract Transcription
            auto transcr = art->get<Transcription>();
            if (transcr)
            {
                const std::string& name = transcr->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << indent(depth) << Transcription::class_name() << ": "<< name << std::endl;
                }
            }

            //Extract TextElement
            auto text = art->get<TextElement>();
            if (text)
            {
                const std::string& name = text->getValue();
                if (log_level >= eLogLevel::DEBUG_LEVEL)
                {
                    std_tracer << indent(depth) << TextElement::class_name() << ": "<< name << std::endl;
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
