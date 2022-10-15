cmake_minimum_required(VERSION 3.15)
project(aras_redux LANGUAGES CXX)

add_executable(ArasRedux)
target_include_directories(ArasRedux include)
target_link_libraries(ArasRedux libArasRedux)