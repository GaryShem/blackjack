project(table)

add_library(table Table.cpp Table.h)

target_include_directories(table PUBLIC .)

target_link_libraries(table cards basics)

add_subdirectory(Players)
target_link_libraries(table players)
