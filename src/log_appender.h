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
#include <fstream>

class LogAppender {
public:
    virtual void Log(std::string content) = 0;

    virtual std::ostream &GetStream() = 0;

};



class OstreamAppender : public LogAppender {
public:
    explicit OstreamAppender(std::ostream* ostream) : _ostream(ostream) { };

    void Log(std::string content) override;

    std::ostream &GetStream() override;

private:
    std::ostream* _ostream;
};



class FileAppender : public LogAppender {
public:
    explicit FileAppender(std::string &logFilePath);

    ~FileAppender();

    void Log(std::string content) override;

    std::ostream &GetStream() override;

private:
    std::string _logFilePath;
    std::ofstream* _fileStream;
};




#endif //LOGGING_TOOLS_LOG_APPENDER_H
