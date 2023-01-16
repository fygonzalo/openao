include(FetchContent)

# ##############################################################################
#
# Downloads and installs asio

FetchContent_Declare(
  asio
  URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-24-0.tar.gz
      CONFIGURE_COMMAND "" BUILD_COMMAND "")

FetchContent_GetProperties(asio)
if(NOT asio_POPULATED)
  FetchContent_Populate(asio)
endif()

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)

# ##############################################################################
#
# Downloads and installs libpqxx

FetchContent_Declare(
  libpqxx URL https://github.com/jtv/libpqxx/archive/refs/tags/7.7.4.tar.gz)

FetchContent_MakeAvailable(libpqxx)

# ##############################################################################
#
# Downloads and installs Base64

FetchContent_Declare(
  base64
  URL https://github.com/ReneNyffenegger/cpp-base64/archive/refs/tags/V2.rc.08.tar.gz
      CONFIGURE_COMMAND
      ""
      BUILD_COMMAND
      "g++ base64.cpp -o base64")

FetchContent_GetProperties(base64)
if(NOT base64_POPULATED)
  FetchContent_Populate(base64)
endif()

add_library(base64 INTERFACE)
target_include_directories(base64 INTERFACE ${base64_SOURCE_DIR})

# ##############################################################################
#
# Configures flags for coverage

if(ENABLE_CODECOVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(ENABLE_CODECOVERAGE)

# ##############################################################################
#
# Defines the static openao library

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
  experimental/serialization/deserializer.h
  experimental/reactor/event.h
  experimental/transport/iclient.h
  experimental/transport/server.h
  experimental/login/account/authenticatecommand.h
  experimental/login/account/accountcontroller.h
  experimental/login/account/accountservice.h
  experimental/login/account/characterlistevent.h
  experimental/login/branches/branchesservice.h
  experimental/di/dependency_injector.h)

target_include_directories(openao PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(openao pqxx base64 asio)

# ##############################################################################
#
# Configures the application executable

add_executable(openao_server main.cpp)
target_include_directories(openao_server INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(openao_server openao)
