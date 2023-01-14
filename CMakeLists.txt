cmake_minimum_required(VERSION 3.18)
project(openao)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/libpqxx build-pqxx)
add_subdirectory(deps/base64)
add_subdirectory(src)
add_subdirectory(test)