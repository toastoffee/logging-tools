cmake_minimum_required(VERSION 3.27)
project(logging_tools)

set(CMAKE_CXX_STANDARD 11)

add_executable(logging_tools main.cpp
        src/logger.cpp
        src/logger.h
        src/log_appender.cpp
        src/log_appender.h
        src/time.hpp)
