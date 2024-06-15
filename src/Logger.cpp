/**
  ******************************************************************************
  * @file           : Logger.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */


#include "Logger.h"

void Logger::SetPriority(LogLevel logLevel) {
    _logLevel = logLevel;
}

void Logger::Log(std::string &logDesc, LogLevel logLevel) {

    if(logLevel > _logLevel) return;

    char logContent[128];

    snprintf(logContent, sizeof(logContent), "[%s]{}", GetCurrentTimeStamp());

}

std::ostream Logger::LogStream(LogLevel logLevel) {

}

