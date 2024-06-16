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

void OstreamAppender::Log(std::string content) const {
    _ostream << content;
}

std::ostream &OstreamAppender::GetStream() const {
    return _ostream;
}
