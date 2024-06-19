#include <iostream>

#include "log.hpp"


int main() {

//    std::string loggerName = "test logger";
//    OstreamAppender coutAppender(std::cout);
//
//    AsyncOStreamAppender asyncCoutAppender(std::cout);
//
//    Logger testLogger(loggerName, asyncCoutAppender);
//
//    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
//    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
//    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);
//    testLogger.Fatal("%s is a clever boy, which has %d brains", "yulu", 1);

    AsyncOstreamAppender asyncTerminalAppender(std::cout);
    asyncTerminalAppender.Log("log by async ostream appender\n");

    AsyncFileAppender asyncFileAppender("./async.log");
    asyncFileAppender.Log("log by async ostream appender\n");

    asyncTerminalAppender.JoinThread();
    asyncFileAppender.JoinThread();
}
