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

#include "buffer.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#define BUF_SEQ_SIZE 3

class LogAppender {
public:
    LogAppender() : _bufUsing(), _buffersWriteIn(), _buffersEmpty() {
        _bufUsing = new Buffer();

        for (int i = 0; i < BUF_SEQ_SIZE; ++i) {
            auto empty = new Buffer;
            _buffersEmpty.push_back(empty);
        }
    };

    virtual void Log(std::string content) = 0;

    virtual std::ostream &GetStream() = 0;

public:
    std::vector<Buffer*> _buffersWriteIn;
    std::vector<Buffer*> _buffersEmpty;
    Buffer* _bufUsing;
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
