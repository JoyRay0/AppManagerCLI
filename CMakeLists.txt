cmake_minimum_required(VERSION 4.2)
project(AppManagerCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(appmanager
        src/Header/Log.hpp
        src/Implementation/Log.cpp
        appmanager.cpp
        src/Header/App.hpp
        src/Implementation/App.cpp
        src/lib/json.hpp
        src/lib/tabulate.hpp
        )

target_include_directories(appmanager PRIVATE
        src/Header
        src/Implementation
        src/lib
)