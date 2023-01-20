# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_game STATIC
  character/charactercontroller.h
  character/commands/authenticatecommand.h
  character/events/characterdetailevent.h
  inventory/commands/loadinventorycommand.h
  inventory/events/loadinventoryevent.h
  inventory/inventorycontroller.h)

target_include_directories(openao_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_game PUBLIC openao_framework)

# ##############################################################################
#
# Configures the generation of the executable
add_executable(openao_game_server main.cpp)

target_link_libraries(openao_game_server openao_game)
