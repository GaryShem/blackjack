project(common_utils)

add_library(common_utils WSAObject.cpp WSAObject.h Utils.cpp Utils.h PlayerDecision.h TcpUtil.cpp TcpUtil.h)

target_link_libraries(common_utils cards)

target_include_directories(common_utils PUBLIC .)