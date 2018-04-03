cmake_minimum_required(VERSION 3.8)
project(linkListUsingXor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp linklist.h linklist.cpp)
add_executable(linkListUsingXor ${SOURCE_FILES})