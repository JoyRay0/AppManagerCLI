cmake_minimum_required(VERSION 4.2)
project(AppManagerCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AppManagerCLI
        src/Header/Log.h
        src/Implementation/Log.cpp
        appmanager.cpp
        src/Header/App.h
        src/Implementation/App.cpp
        src/lib/json.hpp
        )

target_include_directories(AppManagerCLI PRIVATE
        src/Header
        src/Implementation
        src/lib
)