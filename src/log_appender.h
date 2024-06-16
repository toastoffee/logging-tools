/**
  ******************************************************************************
  * @file           : log_appender.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */



#ifndef LOGGING_TOOLS_LOG_APPENDER_H
#define LOGGING_TOOLS_LOG_APPENDER_H

#include <string>
#include <sstream>

class LogAppender {
public:
    virtual void Log(std::string content) const = 0;

    virtual std::ostream  &GetStream() const = 0;

};

class OstreamAppender : public LogAppender {
public:
    explicit OstreamAppender(std::ostream &ostream) : _ostream(ostream) { };

    void Log(std::string content) const override;

    std::ostream &GetStream() const override;

private:
    std::ostream &_ostream;
};

class FileAppender : public LogAppender {
public:
    explicit FileAppender(std::string &logFilePath) : _logFilePath(logFilePath) { };

    void Log(std::string content) const override;

    std::ostream &GetStream() const override;

private:
    std::string _logFilePath;
};




#endif //LOGGING_TOOLS_LOG_APPENDER_H
