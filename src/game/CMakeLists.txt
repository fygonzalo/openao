# ##############################################################################
#
# Configures the generation of the static library

add_library(
  openao_game STATIC
  character/controller.h
  character/manager.h
  character/model/character.h
  character/irepository.h
  character/repository.h
  character/commands/authenticate.h
  character/commands/interact.h
  character/commands/logout.h
  character/events/characterdetail.h
  character/events/loadfunctionbar.h
  character/events/showemote.h
  inventory/commands/loadinventory.h
  inventory/events/loadinventory.h
  inventory/controller.h
  inventory/model/item.h
  inventory/irepository.h
  inventory/repository.h
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
