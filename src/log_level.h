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
    Warn        = 200,
    Info        = 300,
    Debug       = 400,

};



#endif //LOGGING_TOOLS_LOG_LEVEL_H
