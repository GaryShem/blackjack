project(table)

add_library(table Table.cpp Table.h)

target_include_directories(table PUBLIC .)

add_subdirectory(Cards)
target_link_libraries(table cards)

add_subdirectory(Players)
target_link_libraries(table players)