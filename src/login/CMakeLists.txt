# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_login STATIC
  account/accountcontroller.h
  account/commands/authenticatecommand.h
  account/events/characterlistevent.h
  account/repository/accountinfo.h
  account/repository/iaccountrepository.h
  branches/branchesservice.h
  account/events/autherrorevent.h
  account/repository/icharacterrepository.h
  account/repository/characterinfo.h
  postgresql/characterrepository.h
  account/events/announcementevent.h
  account/commands/entergamecommand.h
  account/events/redirectserverevent.h)

target_include_directories(openao_login PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_login PUBLIC openao_database openao_framework)

# ##############################################################################
#
# Configures the generation of the executable

add_executable(openao_login_server main.cpp)
target_link_libraries(openao_login_server PRIVATE openao_login)
