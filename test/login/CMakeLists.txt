add_executable(
  openao_login_test
  account/events/characterlist.cpp account/events/autherror.cpp
  account/events/announcement.cpp account/events/redirectserver.cpp
  account/commands/entergame.cpp)

target_link_libraries(openao_login_test openao_login gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(openao_login_test)
