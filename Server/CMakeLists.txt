project(server)

add_executable(server Table.cpp Table.h main.cpp)

target_include_directories(server PRIVATE .)

target_include_directories(server PRIVATE .)

add_subdirectory(Base)
add_subdirectory(Players)
target_link_libraries(server server_base cards common_utils players)
