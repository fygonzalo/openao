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

target_include_directories(openao PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/asio/asio/include)
target_include_directories(openao_server PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/asio/asio/include)

target_link_libraries(openao_server pqxx)

