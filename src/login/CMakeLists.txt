# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_login STATIC
  account/controller.h
  account/commands/authenticate.h
  account/commands/entergame.h
  account/events/characterlist.h
  account/events/autherror.h
  account/events/announcement.h
  account/events/redirectserver.h
  account/model/info.h
  account/irepository.h
  account/repository.h
  branches/branchesservice.h
  character/irepository.h
  character/repository.h
  character/model/info.h)

target_include_directories(openao_login PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_login PUBLIC openao_database openao_framework)

# ##############################################################################
#
# Configures the generation of the executable

add_executable(openao_login_server main.cpp)
target_link_libraries(openao_login_server PRIVATE openao_login)
