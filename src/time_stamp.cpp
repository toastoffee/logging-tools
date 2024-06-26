/**
  ******************************************************************************
  * @file           : time.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/6/15
  ******************************************************************************
  */

#include "time_stamp.h"

#include <ctime>
#include <chrono>
#include <sstream>

std::string GetCurrentTimeStamp(){

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);

    char buffer[128] = {0};
    strftime(buffer, sizeof(buffer), "%F %T", now_tm);



    return buffer;
}