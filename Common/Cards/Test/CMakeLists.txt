project(card_test)

add_executable(card_test CardTest.cpp CardTest.h)

target_link_libraries(card_test cards gtest)

enable_testing()
add_test(NAME card_test COMMAND card_test)