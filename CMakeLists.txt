cmake_minimum_required(VERSION 3.15)
project(aras_redux LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if (NOT(WIN32))
    add_definitions(-DNCURSES_ENABLED)
endif(WIN32)

add_executable(ArasRedux src/main.cpp)
add_subdirectory(src)
target_include_directories(ArasRedux PRIVATE include)