include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        openao_test
        experimental/chat.cpp experimental/itemmall.cpp experimental/clientmock.h experimental/messagestreammock.h)

target_link_libraries(
        openao_test
        gtest_main
        gmock_main
        openao
)

include(GoogleTest)
gtest_discover_tests(openao_test)
