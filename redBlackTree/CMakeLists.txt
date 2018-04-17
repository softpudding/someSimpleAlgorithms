cmake_minimum_required(VERSION 3.8)
project(redBlackTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp rbtree.h rbtree.cpp)
add_executable(redBlackTree ${SOURCE_FILES})