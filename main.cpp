#include <iostream>

#include "log.hpp"


int main() {

    AsyncOstreamAppender asyncTerminalAppender(std::cout);

    Logger terminalLogger("mainLogger", asyncTerminalAppender, LogLevel::Debug);

    terminalLogger.FATAL("this is a test log");
    terminalLogger.CRITICAL("this is %d test log", 1);
    terminalLogger.ERROR("this is a test log");
    terminalLogger.WARN("this is a test log");
    terminalLogger.DEBUG("this is a test log");
    terminalLogger.INFO("this is a test log");

    asyncTerminalAppender.JoinThread();

    return 0;
}
