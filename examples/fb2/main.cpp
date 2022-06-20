#include <iostream>

#include <txml/applications/fb2/fb2.hpp>

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

        std::unique_ptr<TextReaderWrapper> xml_reader = std::make_unique<TextReaderWrapper>(xdxf_file_path);
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

            //Extract Info section
            auto description = art->node<Description>();
            if (description)
            {
                auto title_info = description->node<TitleInfo>();
                if (title_info)
                {
                    auto book_title = title_info->node<BookTitle>();
                    if (book_title)
                    {
                        std::cout << BookTitle::class_name() << ": " << book_title->value() << std::endl;
                    }
                    auto genre = title_info->node<Genre>();
                    if (genre)
                    {
                        std::cout << Genre::class_name() << ": " << genre->value() << std::endl;
                    }
                    auto lang = title_info->node<Language>();
                    if (lang)
                    {
                        std::cout << Language::class_name() << ": " << lang->value() << std::endl;
                    }
                }
                auto doc_info = description->node<DocumentInfo>();
                if (doc_info)
                {
                    auto author = doc_info->node<Author>();
                    if (author)
                    {
                        auto first_name = author->node<FirstName>();
                        if (first_name)
                        {
                            std::cout << FirstName::class_name() << ": " << first_name->value() << std::endl;
                        }
                        auto middle_name = author->node<MiddleName>();
                        if (middle_name)
                        {
                            std::cout << MiddleName::class_name() << ": " << middle_name->value() << std::endl;
                        }
                        auto last_name = author->node<LastName>();
                        if (last_name)
                        {
                            std::cout << LastName::class_name() << ": " << last_name->value() << std::endl;
                        }
                    }
                }
                auto publish_info = description->node<PublishInfo>();
                if (publish_info)
                {
                    auto publisher = publish_info->node<Publisher>();
                    if (publisher)
                    {
                        std::cout << Publisher::class_name() << ": " << publisher->value() << std::endl;
                    }

                    auto isbn = publish_info->node<ISBN>();
                    if (isbn)
                    {
                        std::cout << ISBN::class_name() << ": " << isbn->value() << std::endl;
                    }
                }
            }
            //Extract inner tags: `Body`
            auto body = art->node<Body>();
            if (body)
            {
                //Extract 'Section'
                const auto& section_container = body->value();
                for (const auto& section : section_container)
                {
                    //Extract array of `Paragraph`s
                    const auto& paragraphs = section->value();
                    for (auto & paragraph : paragraphs)
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
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
