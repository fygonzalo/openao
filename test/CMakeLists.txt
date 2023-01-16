include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ##############################################################################
#
# Configures flags for coverage

if(ENABLE_CODECOVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(ENABLE_CODECOVERAGE)

add_executable(
  openao_test
  experimental/chat.cpp
  experimental/itemmall.cpp
  experimental/reactor.cpp
  experimental/mockmessagestream.h
  experimental/client.cpp
  experimental/deserializer.cpp
  experimental/serialization.cpp
  experimental/mockclient.h
  experimental/account/characterlistevent.cpp
  experimental/di/dependency_injector.cpp)

target_link_libraries(openao_test gtest_main gmock_main openao)

include(GoogleTest)
gtest_discover_tests(openao_test)
