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

    void Fatal(const char *format, ...);
    void Critical(const char *format, ...);
    void Error(const char *format, ...);
    void Warn(const char *format, ...);
    void Info(const char *format, ...);
    void Debug(const char *format, ...);

//    std::ostream &LogStream(LogLevel logLevel);

//    std::ostream &FatalStream();
//    std::ostream &CriticalStream();
//    std::ostream &ErrorStream();
//    std::ostream &WarnStream();
//    std::ostream &InfoStream();
//    std::ostream &DebugStream();

    void Log(LogLevel logLevel, const char *format, va_list args);

private:
//    void Log(LogLevel logLevel, const char *format, ...);

private:
    std::string _name;
    LogAppender &_logAppender;
    LogLevel _logLevel;
};


#endif //LOGGING_TOOLS_LOGGER_H
