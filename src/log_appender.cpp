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

void OstreamAppender::Log(std::string content) const {
    _ostream << content;
}

std::ostream &OstreamAppender::GetStream() const {
    return _ostream;
}

/*
 * FileAppender
 */

void FileAppender::Log(std::string content) const {
    std::fstream f;
    f.open(_logFilePath, std::ios::out|std::ios::app);
    f << content << std::endl;
    f.close();
}

std::ostream &FileAppender::GetStream() const {
    std::fstream f;
    f.open(_logFilePath, std::ios::out|std::ios::app);

    return f;
}
