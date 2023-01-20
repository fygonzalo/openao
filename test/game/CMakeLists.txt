add_executable(
  openao_game_test
  character/charactercontroller.cpp character/authenticatecommand.cpp
  character/characterdetailevent.cpp)

target_link_libraries(openao_game_test openao_game gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(openao_game_test)
