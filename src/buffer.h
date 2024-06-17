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

#define DEFAULT_BUF_SIZE 4096

class Buffer {
private:
    char *_buf;
    int _bufLeft;
    int _bufSize;
public:
    bool isEmpty;

public:
    explicit Buffer(int bufSize = DEFAULT_BUF_SIZE) : _bufSize(bufSize), isEmpty(true), _bufLeft(bufSize){
        _buf = new char[bufSize];
    };

    bool IsEnough(int strLen);

    void Write(const char* str);
};


#endif //LOGGING_TOOLS_BUFFER_H
