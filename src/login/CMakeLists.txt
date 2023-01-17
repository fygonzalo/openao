# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_login STATIC
  account/accountcontroller.h account/accountservice.h
  account/authenticatecommand.h account/characterlistevent.h
  branches/branchesservice.h)

target_include_directories(openao_login PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_login PUBLIC openao_framework)

# ##############################################################################
#
# Configures the generation of the executable

add_executable(openao_login_server main.cpp)
target_link_libraries(openao_login_server openao_login)
