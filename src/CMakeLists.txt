add_library(
  openao STATIC
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
  datasources/impl/pqxx/account.h
  serialization/equipment.h
  serialization/equipment.cpp
  serialization/attributes.h
  serialization/attributes.cpp
  serialization/misc.h
  serialization/misc.cpp
  serialization/branches.h
  serialization/branches.cpp
  experimental/reactor.h
  experimental/game/chat/controller.h
  experimental/ecs/entitymanager.h
  experimental/ecs/componentmanager.h
  experimental/ecs/componentmap.h
  experimental/game/chat/chatmessagecommand.h
  experimental/game/chat/chatmessageevent.h
  experimental/game/stage.h
  experimental/game/itemmall/controller.h
  experimental/game/itemmall/opencommand.h
  experimental/game/itemmall/loadangelgoldevent.h
  experimental/game/itemmall/service.h
  experimental/game/account/accountmanager.h
  experimental/game/account/controller.h
  experimental/game/account/logoutcommand.h
  experimental/game/account/authenticatecommand.h
  experimental/game/account/service.h
  experimental/game/character/service.h
  experimental/game/character/character.h
  experimental/game/character/manager.h
        experimental/serialization/serializer.h
  experimental/transport/imessagestream.h
        experimental/serialization/deserializer.h experimental/reactor/event.h experimental/transport/iclient.h experimental/transport/clientmanager.h)

target_include_directories(
  openao
  PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/deps/asio/asio/include
         ${PROJECT_SOURCE_DIR}/deps/libpqxx/include
         ${PROJECT_SOURCE_DIR}/deps/base64)

target_link_libraries(openao pqxx base64)

add_executable(openao_server main.cpp)

target_include_directories(
  openao_server PUBLIC ${PROJECT_SOURCE_DIR}/src
                       ${PROJECT_SOURCE_DIR}/deps/asio/asio/include)
target_link_libraries(openao_server openao)
