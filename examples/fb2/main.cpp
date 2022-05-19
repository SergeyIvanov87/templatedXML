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
            auto description = art->getValue<Description>();
            if (description)
            {
                auto title_info = description->getValue<TitleInfo>();
                if (title_info)
                {
                    auto book_title = title_info->getValue<BookTitle>();
                    if (book_title)
                    {
                        std::cout << BookTitle::class_name() << ": " << book_title->getValue() << std::endl;
                    }
                    auto genre = title_info->getValue<Genre>();
                    if (genre)
                    {
                        std::cout << Genre::class_name() << ": " << genre->getValue() << std::endl;
                    }
                    auto lang = title_info->getValue<Language>();
                    if (lang)
                    {
                        std::cout << Language::class_name() << ": " << lang->getValue() << std::endl;
                    }
                }
                auto doc_info = description->getValue<DocumentInfo>();
                if (doc_info)
                {
                    auto author = doc_info->getValue<Author>();
                    if (author)
                    {
                        auto first_name = author->getValue<FirstName>();
                        if (first_name)
                        {
                            std::cout << FirstName::class_name() << ": " << first_name->getValue() << std::endl;
                        }
                        auto middle_name = author->getValue<MiddleName>();
                        if (middle_name)
                        {
                            std::cout << MiddleName::class_name() << ": " << middle_name->getValue() << std::endl;
                        }
                        auto last_name = author->getValue<LastName>();
                        if (last_name)
                        {
                            std::cout << LastName::class_name() << ": " << last_name->getValue() << std::endl;
                        }
                    }
                }
                auto publish_info = description->getValue<PublishInfo>();
                if (publish_info)
                {
                    auto publisher = publish_info->getValue<Publisher>();
                    if (publisher)
                    {
                        std::cout << Publisher::class_name() << ": " << publisher->getValue() << std::endl;
                    }

                    auto isbn = publish_info->getValue<ISBN>();
                    if (isbn)
                    {
                        std::cout << ISBN::class_name() << ": " << isbn->getValue() << std::endl;
                    }
                }
            }
            //Extract inner tags: `Body`
            auto body = art->getValue<Body>();
            if (body)
            {
                //Extract 'Section'
                const auto& section_container = body->getValue();
                for (const auto& section : section_container)
                {
                    //Extract array of `Paragraph`s
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
