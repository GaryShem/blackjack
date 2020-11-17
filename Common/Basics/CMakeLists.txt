project(basics)

add_library(basics Bet.cpp Bet.h IPlayer.cpp IPlayer.h ICardDealer.cpp ICardDealer.h Player.cpp Player.h Dealer.h Dealer.cpp Bank.cpp Bank.h)

add_subdirectory(Observer)
add_subdirectory(GameState)

target_link_libraries(basics observer)
target_link_libraries(basics cards)
target_link_libraries(basics gamestate)

target_include_directories(basics PUBLIC .)