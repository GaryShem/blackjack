cmake_minimum_required(VERSION 3.17)
project(blackjack)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "F:/Programming/CPP/Libs/boost_1_74_0")
set(Boost_INCLUDE_DIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)

find_package(Boost REQUIRED)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Client)


