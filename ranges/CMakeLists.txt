cmake_minimum_required(VERSION 3.20)
project(ranges_demo LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 开启 C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ranges_demo ranges01.cpp)
