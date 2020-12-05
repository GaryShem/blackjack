project(common_utils)

add_library(common_utils Utils.cpp Utils.h PlayerDecision.h TcpUtil.cpp TcpUtil.h)

target_include_directories(common_utils PUBLIC ${Boost_INCLUDE_DIR})
target_link_directories(common_utils PUBLIC ${BOOST_LIBRARYDIR})

find_package(Boost REQUIRED)
target_link_libraries(common_utils cards)

target_include_directories(common_utils PUBLIC .)