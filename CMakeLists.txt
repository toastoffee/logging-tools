cmake_minimum_required(VERSION 3.27)
project(logging_tools)

set(CMAKE_CXX_STANDARD 11)

add_executable(logging_tools main.cpp
        src/Logger.cpp
        src/Logger.h
        src/LogAppender.cpp
        src/LogAppender.h)
