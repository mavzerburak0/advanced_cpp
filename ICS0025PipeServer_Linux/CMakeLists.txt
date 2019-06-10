cmake_minimum_required(VERSION 3.13)
project(reader_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(reader_test main.cpp Date.cpp Date.h)