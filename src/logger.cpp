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

void Logger::SetPriority(LogLevel logLevel) {
    _logLevel = logLevel;
}

void Logger::Log(std::string &logDesc, LogLevel logLevel) {

    if(logLevel > _logLevel) return;

    char logContent[128];

    snprintf(logContent, sizeof(logContent), "[%s]{%s} %s",
             GetCurrentTimeStamp().c_str(), toString(logLevel).c_str(), logDesc.c_str());



}

std::ostream Logger::LogStream(LogLevel logLevel) {

}

