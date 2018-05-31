cmake_minimum_required(VERSION 3.8)
project(vEBTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vebtree.h)
add_executable(vEBTree ${SOURCE_FILES})