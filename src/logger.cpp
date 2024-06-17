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
#include "time_stamp.h"

#include <string>
#include <iostream>


std::string toString(const LogLevel &logLevel){
    switch (logLevel) {
        case LogLevel::Fatal:
            return "Fatal";
            break;
        case LogLevel::Critical:
            return "Critical";
            break;
        case LogLevel::Error:
            return "Error";
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

void Logger::Log(LogLevel logLevel, const char *format, va_list args) {
    if(logLevel > _logLevel) return;

    char desc[128];
    vsnprintf(desc, sizeof(desc), format, args);

    char logContent[512];
    snprintf(logContent, sizeof(logContent), "[%s]{%s} %s\n",
             GetCurrentTimeStamp().c_str(), toString(logLevel).c_str(), desc);

    va_end(args);

    _logAppender.Log(logContent);
}

void Logger::Fatal(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Fatal, format, args);

    va_end(args);
}

void Logger::Critical(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Fatal, format, args);

    va_end(args);
}

void Logger::Error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Error, format, args);

    va_end(args);
}

void Logger::Warn(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Warn, format, args);

    va_end(args);
}

void Logger::Info(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Info, format, args);

    va_end(args);
}

void Logger::Debug(const char *format, ...) {
    va_list args;
    va_start(args, format);

    Log(LogLevel::Debug, format, args);

    va_end(args);
}

std::ostream &Logger::LogStream(LogLevel logLevel) {
    char logContent[128];

    snprintf(logContent, sizeof(logContent), "[%s]{%s} ",
             GetCurrentTimeStamp().c_str(), toString(logLevel).c_str());

    return _logAppender.GetStream() << logContent;
}




