include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        openao_test
        transport/security/crypt_xor.cc
        transport/security/crypt_xor2.cc
        transport/connection.cc
        transport/packetheader.cpp
)

target_link_libraries(
        openao_test
        gtest_main
        openao
)

include(GoogleTest)
gtest_discover_tests(openao_test)
