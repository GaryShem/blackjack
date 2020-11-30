project(server_base)
set(CMAKE_CXX_STANDARD 14)


add_library(server_base Dealer.cpp Dealer.h ICardDealer.h IPlayer.cpp IPlayer.h)

target_include_directories(server_base PUBLIC .)

target_link_libraries(server_base cards common_utils)