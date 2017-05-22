cmake_minimum_required(VERSION 3.7)
project(DBCli)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DbConsole.cpp DbConsole.h)
add_executable(DBCli ${SOURCE_FILES})