/**
  ******************************************************************************
  * @file           : log_appender.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */



#ifndef LOGGING_TOOLS_LOG_APPENDER_H
#define LOGGING_TOOLS_LOG_APPENDER_H

#include <string>
#include <iostream>

class LogAppender {
public:
    virtual void Log(std::string content) const = 0;

};

class OstreamAppender : public LogAppender {

    OstreamAppender()
};


#endif //LOGGING_TOOLS_LOG_APPENDER_H
