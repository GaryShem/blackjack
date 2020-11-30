project(client)

add_executable(client TcpPlayerClient.cpp TcpPlayerClient.h PlayerProxy.cpp PlayerProxy.h main.cpp)

target_include_directories(client PRIVATE .)

target_link_libraries(client cards common_utils)