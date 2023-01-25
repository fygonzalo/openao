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
  character/commands/settitle.h
  character/events/characterdetail.h
  character/events/loadfunctionbar.h
  character/events/showemote.h
  character/events/titlechanged.h
  inventory/commands/loadinventory.h
  inventory/commands/moveitem.h
  inventory/events/loadinventory.h
  inventory/events/updateinventory.h
  inventory/controller.h
  inventory/model/inventory.h
  inventory/irepository.h
  inventory/repository.h
  inventory/manager.h
  movement/commands/move.h
  movement/events/move.h
  movement/controller.h
  stage/manager.h
  entity/manager.h
  entity/model/character.h
  entity/events/destroy.h
  chat/commands/say.h
  chat/events/says.h
  chat/controller.h)

target_include_directories(openao_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openao_game PUBLIC openao_database openao_framework)

# ##############################################################################
#
# Configures the generation of the executable
add_executable(openao_game_server main.cpp)

target_link_libraries(openao_game_server openao_game)
