#include <iostream>

#include <txml/applications/fb2/fb2.hpp>

#include "json_deserializer.hpp"
#include "json_deserializer_injection.hpp"

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

    eLogLevel log_level = eLogLevel::ERROR_LEVEL;
    if (argc > 1)
    {
        log_level = static_cast<eLogLevel>(std::max(std::atoi(argv[1]), static_cast<std::underlying_type_t<eLogLevel>>(eLogLevel::ERROR_LEVEL)));
    }

    std::locale::global(std::locale(""));
    StdoutTracer std_tracer;
    EmptyTracer empty_tracer;

    nlohmann::json data
    {
        {"FictionBook", {
            {"description", {
                {"title-info", {
                    {"book-title", {
                        {"#text", "book-title text"}
                    }},
                }},
                {"document-info", {
                }},
                {"publish-info", {
                }}
            }},
            {"body", nlohmann::json::array({
                        nlohmann::json::array({
                            nlohmann::json::object({{"#text", "paragraph_section_0_text_0"}}),
                            nlohmann::json::object({{"#text", "paragraph_section_0_text_1"}})
                            }),
                        nlohmann::json::array({
                            nlohmann::json::object({{"#text", "paragraph_section_1_text_0"}}),
                            nlohmann::json::object({{"#text", "paragraph_section_1_text_1"}})
                            }),
                        nlohmann::json::array({
                            nlohmann::json::object({{"#text", "paragraph_section_2_text_0"}}),
                            nlohmann::json::object({{"#text", "paragraph_section_2_text_1"}}),
                            nlohmann::json::object({{"#text", "paragraph_section_2_text_2"}})
                            })
                    })
            },
        }},
    };

    try
    {
        Fb2FromJSON in(data);
        std::optional<FictionBook> art;
        do {
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                std_tracer << "Dump JSON:\n" << data.dump() << "\n" << std::endl;
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
        auto body = art->getValue<Body>();
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
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    try
    {
        ToInjectedDeserializer in(data);
        std::optional<FictionBook> art;
        do {
            if (log_level >= eLogLevel::DEBUG_LEVEL)
            {
                std_tracer << "Dump JSON:\n" << data.dump() << "\n" << std::endl;
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
        auto body = art->getValue<Body>();
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
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
