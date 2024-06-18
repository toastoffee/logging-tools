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

/*
 * OstreamAppender
 */

void OstreamAppender::Log(std::string content) {

    const char *log = content.c_str();
    int strLen = strlen(log);

    if(_bufUsing->IsEnough(strLen)){
        // write to the buf using if is enough
        _bufUsing->Write(log);
    }else{
        // if full, then switch the _bufUsing with the rear of the _bufs
        _bufUsing->isEmpty = false;
        _buffersWriteIn.push_back(_bufUsing);

        // set the _bufUsing the rear of emptys
        _bufUsing = _buffersEmpty.back();
        _buffersEmpty.pop_back();

        _bufUsing->Write(log);
    }

}

std::ostream &OstreamAppender::GetStream() {
    return *_ostream;
}

/*
 * FileAppender
 */

FileAppender::FileAppender(std::string &logFilePath) : _logFilePath(logFilePath) {

    _fileStream = new std::ofstream();
    _fileStream->open(logFilePath , std::ios::out|std::ios::app);
}

FileAppender::~FileAppender() {
    _fileStream->close();
}


void FileAppender::Log(std::string content) {
    *_fileStream << content << std::endl;
}

std::ostream &FileAppender::GetStream() {
    return *_fileStream;
}
