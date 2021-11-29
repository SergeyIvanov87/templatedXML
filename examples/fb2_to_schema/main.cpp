#include <iostream>

#include <txml/applications/fb2/fb2.hpp>
#include "fb2_to_custom_schema.hpp"
#include "fb2_to_json_schema.hpp"
#include "fb2_to_json_schema_repack.hpp"
#include "fb2_to_json_schema_injection.hpp"

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
        log_level = static_cast<eLogLevel>(std::max(std::atoi(argv[2]), static_cast<std::underlying_type_t<eLogLevel>>(eLogLevel::ERROR_LEVEL)));
    }

    std::locale::global(std::locale(""));

    std::cout << "Serialize to custom schema: ";
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        // Declare serializer object
        ToCustomSchema<std::ostream> serializer(std::cout);

        //To schema
        if (log_level >= eLogLevel::DEBUG_LEVEL)
        {
             FictionBook::schema_serialize(serializer, std_tracer);
        }
        else
        {
            FictionBook::schema_serialize(serializer, empty_tracer);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    std::cout << "Serialize to JSON schema: ";
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        // Declare serializer object
        ToJSONSchema serializer;

        //To schema
        nlohmann::json data;
        if (log_level >= eLogLevel::DEBUG_LEVEL)
        {
            FictionBook::schema_serialize(serializer, std_tracer);
             data = serializer.finalize(std_tracer);
        }
        else
        {
            FictionBook::schema_serialize(serializer, empty_tracer);
            data = serializer.finalize(empty_tracer);
        }

        std::cout << data.dump() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    std::cout << "Serialize to ToJSONSchemaWithRepack schema : ";
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        // Declare serializer object
        ToJSONSchemaWithRepack serializer;

        //To schema with repack: wrap out every Node in "property" object
        nlohmann::json data;
        if (log_level >= eLogLevel::DEBUG_LEVEL)
        {
            FictionBook::schema_serialize(serializer, std_tracer);
            data = serializer.finalize(std_tracer);
        }
        else
        {
            FictionBook::schema_serialize(serializer, empty_tracer);
            data = serializer.finalize(empty_tracer);
        }

        std::cout << data.dump() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    std::cout << "Serialize to ToJSONInjectionSchema schema : ";
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        // Declare serializer object
        ToInjectedSchema serializer;

        //To schema with injection: combine TWO kind of serializers in one: some Nodes are serialized,
        // but some other  serialized with repack: text element wrapped by "property" object
        nlohmann::json data;
        if (log_level >= eLogLevel::DEBUG_LEVEL)
        {
            FictionBook::schema_serialize(serializer, std_tracer);
            data = serializer.finalize(std_tracer);
        }
        else
        {
            FictionBook::schema_serialize(serializer, empty_tracer);
            data = serializer.finalize(empty_tracer);
        }

        std::cout << data.dump() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
