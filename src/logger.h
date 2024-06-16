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

#include "log_level.h"
#include "log_appender.h"

class Logger {
public:

    Logger(std::string &name, LogAppender &logAppender) :
    _name(name), _logAppender(logAppender), _logLevel(LogLevel::Debug) { }

    void SetPriority(LogLevel logLevel);

    void Log(std::string &logDesc, LogLevel logLevel);

    void Fatal(std::string &logDesc);
    void Critical(std::string &logDesc);
    void Error(std::string &logDesc);
    void Warn(std::string &logDesc);
    void Info(std::string &logDesc);
    void Debug(std::string &logDesc);

    std::ostream &LogStream(LogLevel logLevel);

    std::ostream &FatalStream();
    std::ostream &CriticalStream();
    std::ostream &ErrorStream();
    std::ostream &WarnStream();
    std::ostream &InfoStream();
    std::ostream &DebugStream();

private:
    std::string _name;
    LogAppender &_logAppender;
    LogLevel _logLevel;
};


#endif //LOGGING_TOOLS_LOGGER_H
