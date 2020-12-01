project(client)

add_executable(client TcpPlayerClient.cpp TcpPlayerClient.h PlayerProxy.cpp PlayerProxy.h main.cpp TcpBotClient.cpp TcpBotClient.h TcpConsoleClient.cpp TcpConsoleClient.h)

target_include_directories(client PRIVATE .)

target_link_libraries(client cards common_utils)