project(client)

add_executable(client TcpPlayerClient.cpp TcpPlayerClient.h PlayerProxy.cpp PlayerProxy.h main.cpp TcpBotClient.cpp TcpBotClient.h TcpConsoleClient.cpp TcpConsoleClient.h)

find_package(Boost REQUIRED)
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(client PRIVATE .)

target_link_libraries(client cards common_utils)
target_link_directories(client PRIVATE ${BOOST_LIBRARYDIR})