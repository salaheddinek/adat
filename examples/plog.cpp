#include "adat/plog/Log.h"
#include "adat/plog/Init.h"

int main()
{
    plog::Init::console_and_file_logger("log.csv", plog::Severity::debug);


    PLOGI << "Hello log!"; // short macro
    PLOG_DEBUG << "Hello log!"; // long macro
    pPLOG(plog::error) << "Hello log!"; // function-style macro

    // Also you can use LOG_XXX macro but it may clash with other logging libraries
    LOGD << "Hello log!"; // short macro
    LOG_WARNING << "Hello log!"; // long macro
    return (0);
}

