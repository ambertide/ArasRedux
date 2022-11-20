cmake_minimum_required(VERSION 3.15)
project(aras_redux LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE "Debug")

set(INCLUDE_DIRECTORIES_LIST include)
set(LINK_LIBRARIES_LIST)

find_package(Curses)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if (${CURSES_FOUND})
    message(STATUS "Curses found, TerminalGraphicsService will use curses.")
    add_definitions(-DNCURSES_ENABLED)
    set(INCLUDE_DIRECTORIES_LIST ${INCLUDE_DIRECTORIES_LIST} ${CURSES_INCLUDE_DIR})
    set(LINK_LIBRARIES_LIST ${LINK_LIBRARIES_LIST} ${CURSES_LIBRARIES})
else (${CURSES_FOUND})
    message(WARNING "Curses not found. TerminalGraphicsService won't work.")
endif(${CURSES_FOUND})

add_executable(ArasRedux src/main.cpp)
add_subdirectory(src)
target_include_directories(ArasRedux PRIVATE ${INCLUDE_DIRECTORIES_LIST})
target_link_libraries(ArasRedux ${LINK_LIBRARIES_LIST})
