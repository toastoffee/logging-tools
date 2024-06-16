/**
  ******************************************************************************
  * @file           : log_level.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/14
  ******************************************************************************
  */



#ifndef LOGGING_TOOLS_LOG_LEVEL_H
#define LOGGING_TOOLS_LOG_LEVEL_H


enum class LogLevel : unsigned int {

    Fatal       = 0,
    Critical    = 100,
    Error       = 200,
    Warn        = 300,
    Info        = 400,
    Debug       = 500,

};



#endif //LOGGING_TOOLS_LOG_LEVEL_H
