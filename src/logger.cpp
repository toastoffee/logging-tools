/**
  ******************************************************************************
  * @file           : Logger.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */


#include "logger.h"

std::string toString(const LogLevel &logLevel){
    switch (logLevel) {
        case LogLevel::Fatal:
            return "Fatal";
            break;
        case LogLevel::Critical:
            return "Critical";
            break;
        case LogLevel::Warn:
            return "Warn";
            break;
        case LogLevel::Info:
            return "Info";
            break;
        case LogLevel::Debug:
            return "Debug";
            break;
    }
}

void Logger::SetPriority(LogLevel logLevel) {
    _logLevel = logLevel;
}

void Logger::Log(std::string &logDesc, LogLevel logLevel) {

    if(logLevel > _logLevel) return;

    char logContent[128];

    snprintf(logContent, sizeof(logContent), "[%s]{%s} %s\n",
             GetCurrentTimeStamp().c_str(), toString(logLevel).c_str(), logDesc.c_str());

    _logAppender.Log(logContent);

}

std::ostream &Logger::LogStream(LogLevel logLevel) {
    char logContent[128];

    snprintf(logContent, sizeof(logContent), "[%s]{%s} ",
             GetCurrentTimeStamp().c_str(), toString(logLevel).c_str());

    return _logAppender.GetStream() << logContent;
}

