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
#include "../log.hpp"


#include <string>
#include <iostream>
#include <cstring>

Buffer::Buffer(int bufSize) : _buf(new char[bufSize]), _bufSize(bufSize), _bufLen(0)
{
}

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

