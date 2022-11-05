cmake_minimum_required(VERSION 3.15)
project(aras_redux LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_DIRECTORIES_LIST include)
set(LINK_LIBRARIES_LIST)

if (NOT(WIN32))
    add_definitions(-DNCURSES_ENABLED)
    find_package(Curses REQUIRED)
    set(INCLUDE_DIRECTORIES_LIST ${INCLUDE_DIRECTORIES_LIST} ${CURSES_INCLUDE_DIR})
    set(LINK_LIBRARIES_LIST ${LINK_LIBRARIES_LIST} ${CURSES_LIBRARIES})
endif(NOT(WIN32))

add_executable(ArasRedux src/main.cpp)
add_subdirectory(src)
target_include_directories(ArasRedux PRIVATE ${INCLUDE_DIRECTORIES_LIST})
target_link_libraries(ArasRedux ${LINK_LIBRARIES_LIST})
