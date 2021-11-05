#include <iostream>

#include <txml/applications/fb2/fb2.hpp>
#include "fb2_to_schema.hpp"

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
    try
    {
        StdoutTracer std_tracer;
        EmptyTracer empty_tracer;

        // Declare serializer object
        ToSchema<std::ostream> serializer(std::cout);

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
}
