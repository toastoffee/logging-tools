/**
 ******************************************************************************
 * @file           : buffer.h
 * @author         : toastoffee
 * @brief          : None
 * @attention      : None
 * @date           : 2024/6/17
 ******************************************************************************
 */

#ifndef LOGGING_TOOLS_BUFFER_H
#define LOGGING_TOOLS_BUFFER_H

#define DEFAULT_BUF_SIZE 150

class Buffer
{
public:
    explicit Buffer(int bufSize = DEFAULT_BUF_SIZE);
    ~Buffer();

    bool Write(const char *str, int len);
    void GetData(char*& buf, int& len);

private:
    char *_buf;
    int _bufLen;
    int _bufSize;
};

#endif // LOGGING_TOOLS_BUFFER_H
