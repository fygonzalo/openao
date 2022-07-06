include(FetchContent)
FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz
)
FetchContent_MakeAvailable(boost)

add_library(openao STATIC
        main.cpp
        transport/security/crypt_xor.h
        transport/security/crypt_xor2.h
        transport/packetheader.h
        transport/messagestream.h
        transport/server.h
)

add_executable(openao_server
        main.cpp
        transport/checksum.h
        transport/security/crypt_xor.h
        transport/security/crypt_xor2.h
        transport/packetheader.h
        transport/messagestream.h
        transport/server.h
)

target_include_directories(openao PUBLIC ${PROJECT_SOURCE_DIR}/src ${boost_SOURCE_DIR})
target_include_directories(openao_server PUBLIC ${PROJECT_SOURCE_DIR}/src ${boost_SOURCE_DIR})

target_link_libraries(openao_server PRIVATE pqxx)

