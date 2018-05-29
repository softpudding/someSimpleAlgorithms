cmake_minimum_required(VERSION 3.8)
project(Btree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp btree.h)
add_executable(Btree ${SOURCE_FILES})