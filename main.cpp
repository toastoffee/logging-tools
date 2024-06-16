#include <iostream>
#include <string>

#include "src/logger.h"


int main() {

    std::string loggerName = "test logger";
    OstreamAppender coutAppender(std::cout);

    Logger testLogger(loggerName, coutAppender);

    std::string log = "this is a test log";
    testLogger.Log(log, LogLevel::Warn);

    testLogger.LogStream(LogLevel::Warn) << "log by log Stream\n";


    std::string fileLoggerName = "file logger";
    std::string fileLogPath = "./test.log";
    FileAppender fileAppender(fileLogPath, <#initializer#>);

    Logger testFileLogger(fileLoggerName, fileAppender);

    testFileLogger.Log(log, LogLevel::Warn);

    testFileLogger.LogStream(LogLevel::Warn) << "log by log Stream\n";
}
