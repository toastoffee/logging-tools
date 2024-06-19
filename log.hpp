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
/**************************** [Base] ****************************/

/*
 * base class of Appender
 */
class LogAppender
{
public:
    virtual void Log(const char* content) = 0;
};




/*
 * the sync abstract version of LogAppender
 */
class SyncLogAppender : public LogAppender
{
public:
    virtual void Log(const char* content);

private:
    virtual void Output(const char* content) = 0;
};

void SyncLogAppender::Log(const char *content) {
    Output(content);
}



/*
 * the async abstract version of
 *
 *
 *
 *      LogAppender
 */
class AsyncLogAppender : public LogAppender
{
public:

    void Log(const char* content) override;

    void JoinThread();

private:
    void WriteThread();

    virtual void Output(const char* content) = 0;

private:
    bool _isRunning;

    std::mutex _mu;
    std::condition_variable _cond;

    std::thread _writeThread;

    Buffer *_currentBuffer;
    std::queue<Buffer *> _buffers;
};

void AsyncLogAppender::JoinThread() {
    _isRunning = false;
    _cond.notify_one();
    _writeThread.join();
}

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


/**************************** [LogAppender] ****************************/
/**************************** [some implementation] ****************************/

class SyncOstreamAppender : public SyncLogAppender
{
public:
    explicit SyncOstreamAppender(std::ostream &ostream) : _ostream(ostream){};

private:
    void Output(const char* content) override;

private:
    std::ostream &_ostream;
};

void SyncOstreamAppender::Output(const char *content) {
    _ostream << content;
}



class AsyncOstreamAppender : public AsyncLogAppender
{
public:
    explicit AsyncOstreamAppender(std::ostream &ostream) : _ostream(ostream){};

private:
    void Output(const char* content) override;

private:
    std::ostream &_ostream;
};

void AsyncOstreamAppender::Output(const char *content) {
    _ostream << content;
}



class SyncFileAppender : public SyncLogAppender
{
public:
    explicit SyncFileAppender(const std::string &logFilePath);

private:
    void Output(const char *content) override;

private:
    std::string _logFilePath;
    std::ofstream _fileStream;
};

SyncFileAppender::SyncFileAppender(const std::string &logFilePath) : _logFilePath(logFilePath) { }

void SyncFileAppender::Output(const char *content) {
    _fileStream.open(_logFilePath, std::ios::out | std::ios::app);
    _fileStream << content;
    _fileStream.close();
}



class AsyncFileAppender : public AsyncLogAppender
{
public:
    explicit AsyncFileAppender(const std::string &logFilePath);

private:
    void Output(const char *content) override;

private:
    std::string _logFilePath;
    std::ofstream _fileStream;
};

AsyncFileAppender::AsyncFileAppender(const std::string &logFilePath) : _logFilePath(logFilePath) { }

void AsyncFileAppender::Output(const char *content) {
    _fileStream.open(_logFilePath, std::ios::out | std::ios::app);
    _fileStream << content;
    _fileStream.close();
}


#endif // TOAST_LOG_HPP
