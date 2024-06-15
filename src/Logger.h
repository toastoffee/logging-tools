/**
  ******************************************************************************
  * @file           : Logger.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */



#ifndef LOGGING_TOOLS_LOGGER_H
#define LOGGING_TOOLS_LOGGER_H

#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>

#include "log_level.h"
#include "LogAppender.h"
#include "time.hpp"

class Logger {
public:
    explicit Logger(std::string &name, LogAppender &logAppender) : _name(name), _logAppender(logAppender) { }

    void SetPriority(LogLevel logLevel);

    void Log(std::string &logDesc, LogLevel logLevel);

    std::ostream LogStream(LogLevel logLevel);

private:
    std::string _name;
    LogAppender &_logAppender;
    LogLevel _logLevel;
};


#endif //LOGGING_TOOLS_LOGGER_H
