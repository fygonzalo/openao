# ##############################################################################
#
# Configures flags for coverage

if(ENABLE_CODECOVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(ENABLE_CODECOVERAGE)

# ##############################################################################
#
# Configures test executable
add_executable(openao_framework_test utils/bitset.cpp)

target_link_libraries(openao_framework_test openao_framework gtest_main
                      gmock_main)

include(GoogleTest)
gtest_discover_tests(openao_framework_test)
