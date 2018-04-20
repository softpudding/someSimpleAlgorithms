cmake_minimum_required(VERSION 3.8)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp avltree.h avltree.cpp)
add_executable(AVLTree ${SOURCE_FILES})