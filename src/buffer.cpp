/**
  ******************************************************************************
  * @file           : buffer.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/17
  ******************************************************************************
  */



#include "buffer.h"
#include <string>
#include <iostream>

bool Buffer::IsEnough(int strLen)
{
    if(_bufLeft >= strLen){
        return true;
    }
    return false;
}

void Buffer::Write(const char *str) {
    strcpy(_buf + _bufSize - _bufLeft, str);
    _bufLeft -= sizeof(str);

    std::cout << _buf << std::endl;
}
