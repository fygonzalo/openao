add_executable(
  openao_game_test
  character/charactercontroller.cpp
  character/commands/authenticate.cpp
  character/commands/interact.cpp
  character/events/characterdetail.cpp
  character/events/showemote.cpp
  entity/model/npc.cpp
  inventory/events/loadinventory.cpp
  movement/commands/move.cpp
  movement/events/move.cpp)

target_link_libraries(openao_game_test openao_game gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(openao_game_test)
