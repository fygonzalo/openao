cmake_minimum_required(VERSION 3.18)
project(openao)

set(CMAKE_CXX_STANDARD 20)

# ##############################################################################
#
# Configures flags for coverage

if(ENABLE_CODECOVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(ENABLE_CODECOVERAGE)

add_subdirectory(src)
add_subdirectory(test)
