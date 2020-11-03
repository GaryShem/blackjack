cmake_minimum_required(VERSION 3.17)
project(blackjack)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Table Table)

add_executable(blackjack main.cpp)

target_link_libraries(blackjack PUBLIC table)
