project(players)

add_library(players STATIC TcpPlayerServer.cpp TcpPlayerServer.h ConsolePlayer.cpp ConsolePlayer.h)

target_include_directories(players PUBLIC .)

target_link_libraries(players cards common_utils server_base)