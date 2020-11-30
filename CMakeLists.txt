cmake_minimum_required(VERSION 3.17)
project(blackjack)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Client)


