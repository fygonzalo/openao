add_library(openao STATIC
        main.cpp
        transport/security/crypt_xor.h
        transport/security/crypt_xor2.h
        transport/packetheader.h
        transport/messagestream.h
        transport/server.h
        transport/client.h
        )

add_executable(openao_server
        main.cpp
        transport/checksum.h
        transport/security/crypt_xor.h
        transport/security/crypt_xor2.h
        transport/packetheader.h
        transport/messagestream.h
        transport/server.h
        transport/client.h
        transport/checksum.h
        transport/checksum.cpp
        game/playermanager.h
        game/playermanager.cpp
        datasources/impl/pqxx/common/character.h
        datasources/impl/pqxx/common/character.cpp
        datasources/impl/pqxx/common/attributes.h
        datasources/impl/pqxx/common/attributes.cpp
        datasources/impl/pqxx/common/equipment.h
        datasources/impl/pqxx/common/equipment.cpp
        datasources/impl/pqxx/common/misc.h
        datasources/impl/pqxx/common/misc.cpp
        datasources/impl/pqxx/common/position.h
        datasources/impl/pqxx/common/position.cpp
        datasources/impl/pqxx/common/stats.h
        datasources/impl/pqxx/common/stats.cpp
        serialization/equipment.h
        serialization/equipment.cpp
        serialization/attributes.h
        serialization/attributes.cpp
        serialization/misc.h
        serialization/misc.cpp
        serialization/branches.h
        serialization/branches.cpp
        )

target_include_directories(openao PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/asio/asio/include)
target_include_directories(openao_server PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/asio/asio/include)

target_link_libraries(openao_server pqxx base64)

