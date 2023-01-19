include(FetchContent)

# ##############################################################################
#
# Downloads and installs asio

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio
  GIT_TAG asio-1-24-0)

FetchContent_GetProperties(asio)
if(NOT asio_POPULATED)
  FetchContent_Populate(asio)
endif()

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)

# ##############################################################################
#
# Downloads and installs sqlpp11

FetchContent_Declare(
  sqlpp11
  GIT_REPOSITORY https://github.com/rbock/sqlpp11
  GIT_TAG 0.61)
FetchContent_MakeAvailable(sqlpp11)

# ##############################################################################
#
# Downloads and installs Base64

FetchContent_Declare(
  base64
  GIT_REPOSITORY https://github.com/ReneNyffenegger/cpp-base64
  GIT_TAG V2.rc.08
  BUILD_COMMAND
  "g++ base64.cpp -o base64")

FetchContent_GetProperties(base64)
if(NOT base64_POPULATED)
  FetchContent_Populate(base64)
endif()

add_library(base64 STATIC ${base64_SOURCE_DIR}/base64.cpp)
target_include_directories(base64 INTERFACE ${base64_SOURCE_DIR})

# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_framework STATIC
  di/dependency_injector.h
  ecs/componentmanager.h
  ecs/componentmap.h
  ecs/entitymanager.h
  security/ciphersuite.h
  security/crypt_xor.h
  security/crypt_xor2.h
  serialization/deserializer.h
  serialization/serializer.h
  transport/checksum.cpp
  transport/checksum.h
  transport/client.h
  transport/customreactor.h
  transport/iclient.h
  transport/imessagestream.h
  transport/messagestream.h
  transport/packetheader.h
  transport/server.h
  utils/binarybuffer.h
  utils/bitset.h
  utils/flagset.h
  utils/string.h
  di/injectable.h)

target_include_directories(openao_framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_framework PUBLIC base64 sqlpp11 pq asio)
