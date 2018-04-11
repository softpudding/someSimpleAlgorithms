cmake_minimum_required(VERSION 3.8)
project(binarySearchTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tree.h tree.cpp)
add_executable(binarySearchTree ${SOURCE_FILES})