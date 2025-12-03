cmake_minimum_required(VERSION 3.20)

project(retrieval)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(for_each_example for_each.cpp)
