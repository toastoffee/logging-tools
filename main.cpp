#include <iostream>
#include <string>

#include "src/logger.h"


int main() {

    std::string loggerName = "test logger";
    OstreamAppender coutAppender(std::cout);

    AsyncOStreamAppender asyncCoutAppender(std::cout);
    asyncCoutAppender.Start();

    Logger testLogger(loggerName, asyncCoutAppender);

    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);

    asyncCoutAppender.Stop();

//    std::string fileLoggerName = "file logger";
//    std::string fileLogPath = "./test.log";
//    FileAppender fileAppender(fileLogPath);
//
//    Logger testFileLogger(fileLoggerName, fileAppender);
//
//    testFileLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
//
}
