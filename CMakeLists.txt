cmake_minimum_required(VERSION 4.2)
project(AppManagerCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/Header)
include_directories(src/Implementation)

add_executable(AppManagerCLI
        src/Header/Log.h
        src/Implementation/Log.cpp
        appmanager.cpp)
