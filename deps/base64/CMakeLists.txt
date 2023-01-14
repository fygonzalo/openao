cmake_minimum_required(VERSION 3.18)
project(base64)

set(CMAKE_CXX_STANDARD 20)

add_library(base64 STATIC base64.h base64.cpp)

target_include_directories(base64 PUBLIC ${PROJECT_SOURCE_DIR})