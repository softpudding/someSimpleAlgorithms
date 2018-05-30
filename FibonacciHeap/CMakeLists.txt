cmake_minimum_required(VERSION 3.8)
project(FibonacciHeap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp fibheap.h fibheap.cpp)
add_executable(FibonacciHeap ${SOURCE_FILES})