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
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class LogAppender
{
public:
    virtual void Log(const std::string &content) = 0;
};

class OstreamAppender : public LogAppender
{
public:
    explicit OstreamAppender(std::ostream &ostream) : _ostream(ostream){};

    virtual void Log(const std::string &content);

private:
    std::ostream &_ostream;
};

class FileAppender : public LogAppender
{
public:
    explicit FileAppender(const std::string &logFilePath);
    ~FileAppender();

    virtual void Log(const std::string &content);

private:
    std::string _logFilePath;
    std::ofstream _fileStream;
};

class AsyncOStreamAppender : public LogAppender
{
public:
    AsyncOStreamAppender(std::ostream &ostream);
    virtual ~AsyncOStreamAppender();

    virtual void Log(const std::string &content);

private:
    void WriteThread();

    void Start();
    void Stop();

private:
    bool _running;

    std::ostream &_ostream;

    std::mutex _mu;
    std::condition_variable _cond;

    std::thread _writeThread;

    Buffer *_currentBuffer;
    std::queue<Buffer *> _buffers;
};

#endif // LOGGING_TOOLS_LOG_APPENDER_H
