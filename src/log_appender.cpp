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


/*
 * OstreamAppender
 */

void OstreamAppender::Log(std::string content) {
    _ostream << content;
}

std::ostream OstreamAppender::GetStream() const {
    return _ostream;
}

/*
 * FileAppender
 */

FileAppender::FileAppender(std::string &logFilePath) :
    _logFilePath(logFilePath), _fileStream(std::ofstream(logFilePath, std::ios::out|std::ios::app)){;
}

void FileAppender::Log(std::string content) {
    _fileStream << content << std::endl;
}

std::ostream &FileAppender::GetStream() const {

    return _fileStream;
}
