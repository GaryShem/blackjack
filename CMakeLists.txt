cmake_minimum_required(VERSION 3.17)
project(blackjack)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Client)


