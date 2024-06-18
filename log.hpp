/**
  ******************************************************************************
  * @file           : log.hpp
  * @author         : toastoffee
  * @brief          : a header-only file that supports log system
  * @attention      : None
  * @date           : 2024/6/18
  ******************************************************************************
  */



#ifndef TOAST_LOG_HPP
#define TOAST_LOG_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

#define DEFAULT_BUF_SIZE 1024


/**************************** [Buffer] ****************************/

/*
 * container of string that helps store and get the buffer
 */
class Buffer
{
public:
    explicit Buffer(int bufSize = DEFAULT_BUF_SIZE);    // initialization with buf size
    ~Buffer();                                          // delete _buf

    bool Write(const char *str, int len);               // write the str to _buf
    void GetData(char*& buf, int& len);                 // get the _buf data and size

private:
    char *_buf;                                         // where data stores
    int _bufLen;                                        // current data length
    int _bufSize;                                       // the data buffer maximum size
};

Buffer::Buffer(int bufSize) : _buf(new char[bufSize]), _bufSize(bufSize), _bufLen(0) { }

bool Buffer::Write(const char *str, int len)
{
    if (_bufLen + len > _bufSize)
    {
        return false;
    }

    memcpy(_buf + _bufLen, str, len);
    _bufLen += len;

    return true;
}

void Buffer::GetData(char*& buffer, int& len)
{
    buffer = _buf;
    len = _bufLen;
}

Buffer::~Buffer() {
    delete[] _buf;
}


/**************************** [LogAppender] ****************************/

class LogAppender
{
public:
    virtual void Log(const char* content) = 0;
};

class SyncLogAppender : public LogAppender
{
public:
    virtual void Log(const char* content);

private:
    virtual void Output(const char* content) = 0;
};

class AsyncLogAppender : public LogAppender
{
public:

    virtual void Log(const char* content);

private:
    virtual void WriteThread();

    virtual void Output(const char* content) = 0;

private:
    bool _isRunning;

    std::mutex _mu;
    std::condition_variable _cond;

    std::thread _writeThread;

    Buffer *_currentBuffer;
    std::queue<Buffer *> _buffers;
};

void AsyncLogAppender::Log(const char* content) {
    if(!_isRunning){
        _isRunning = true;
        _currentBuffer = new Buffer();
        _writeThread = std::thread(&AsyncLogAppender::WriteThread, this);
    }

    std::lock_guard<std::mutex> lock(_mu);
    if (!_currentBuffer->Write(content, strlen(content)))
    {
        _buffers.push(_currentBuffer);

        _currentBuffer = new Buffer();

        _currentBuffer->Write(content, strlen(content));
        _cond.notify_one();
    }
}

void AsyncLogAppender::WriteThread() {
    std::queue<Buffer *> buffersToWrite;
    while (_isRunning)
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

            Output(data);

            delete buffer;
            buffersToWrite.pop();
        }
    }
}


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

#endif // TOAST_LOG_HPP
