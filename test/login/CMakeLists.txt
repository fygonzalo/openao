add_executable(
  openao_login_test
  account/events/characterlistevent.cpp account/events/autherrorevent.cpp
  account/events/announcementevent.cpp account/events/redirectserverevent.cpp
  account/commands/entergamecommand.cpp)

target_link_libraries(openao_login_test openao_login gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(openao_login_test)
