/**
 ******************************************************************************
 * @file           : log_appender.cpp
 * @author         : toastoffee
 * @brief          : None
 * @attention      : None
 * @date           : 2024/6/14
 ******************************************************************************
 */

#include "log_appender.h"

#include <fstream>
#include <iostream>
#include <cstring>

/*
 * OstreamAppender
 */

void OstreamAppender::Log(const std::string &content)
{
    _ostream << content;
}

/*
 * FileAppender
 */

FileAppender::FileAppender(const std::string &logFilePath) : _logFilePath(logFilePath)
{
    _fileStream.open(logFilePath, std::ios::out | std::ios::app);
}

FileAppender::~FileAppender()
{
    _fileStream.close();
}

void FileAppender::Log(const std::string &content)
{
    _fileStream << content << std::endl;
}

AsyncOStreamAppender::AsyncOStreamAppender(std::ostream &ostream) : _ostream(ostream), _running(false), _currentBuffer(nullptr)
{
}

AsyncOStreamAppender::~AsyncOStreamAppender()
{
}

void AsyncOStreamAppender::Start()
{
    _running = true;
    _currentBuffer = new Buffer();
    _writeThread = std::thread(&AsyncOStreamAppender::WriteThread, this);
}

void AsyncOStreamAppender::Stop()
{
    _running = false;
    _cond.notify_one();
    _writeThread.join();
}

void AsyncOStreamAppender::Log(const std::string &content)
{
    std::lock_guard<std::mutex> lock(_mu);
    if (!_currentBuffer->Write(content.c_str(), content.size()))
    {
        _buffers.push(_currentBuffer);

        _currentBuffer = new Buffer();

        _currentBuffer->Write(content.c_str(), content.size());
        _cond.notify_one();
    }
}

void AsyncOStreamAppender::WriteThread()
{
    std::queue<Buffer *> buffersToWrite;
    while (_running)
    {
        {
            std::unique_lock<std::mutex> lock(_mu);
            if (_buffers.empty())
            {
                _cond.wait_for(lock, std::chrono::milliseconds(3000));
            }

            _buffers.push(_currentBuffer);
            _currentBuffer = new Buffer();

            buffersToWrite.swap(_buffers);
        }

        while (!buffersToWrite.empty())
        {
            Buffer *buffer = buffersToWrite.front();
            char *data;
            int len;
            buffer->GetData(data, len);
            std::string str(data, len);
            _ostream << str;

            delete buffer;
            buffersToWrite.pop();
        }
    }
}
