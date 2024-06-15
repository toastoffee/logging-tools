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

std::string toString(const LogLevel &logLevel){
    switch (logLevel) {
        case LogLevel::Fatal:
            return "Fatal";
            break;
        case LogLevel::Critical:
            return "Critical";
            break;
        case LogLevel::Warn:
            return "Warn";
            break;
        case LogLevel::Info:
            return "Info";
            break;
        case LogLevel::Debug:
            return "Debug";
            break;
    }
}


#endif //LOGGING_TOOLS_LOG_LEVEL_H
