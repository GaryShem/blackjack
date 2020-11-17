project(players)

add_library(players STATIC IPlayer.cpp IPlayer.h IDealer.cpp IDealer.h Dealer.cpp Dealer.h)

target_include_directories(players PUBLIC .)

add_subdirectory(PlayerImplementations)

target_link_libraries(players cards)
target_link_libraries(players pimpl)