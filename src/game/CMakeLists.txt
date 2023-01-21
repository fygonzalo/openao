# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_game STATIC
  character/charactercontroller.h
  character/charactermanager.h
  character/commands/authenticatecommand.h
  character/commands/interact.h
  character/events/characterdetailevent.h
  character/events/loadfunctionbarevent.h
  character/events/showemote.h
  character/repositories/icharacterrepository.h
  character/repositories/impl/characterrepository.h
  inventory/commands/loadinventorycommand.h
  inventory/events/loadinventoryevent.h
  inventory/inventorycontroller.h
  inventory/repositories/iinventoryrepository.h
  inventory/repositories/impl/inventoryrepository.h
  movement/commands/move.h
  movement/events/move.h
  movement/controller.h)

target_include_directories(openao_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_game PUBLIC openao_database openao_framework)

# ##############################################################################
#
# Configures the generation of the executable
add_executable(openao_game_server main.cpp)

target_link_libraries(openao_game_server openao_game)
