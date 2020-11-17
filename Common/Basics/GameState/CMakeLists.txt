project(gamestate)

add_library(gamestate GameState.cpp GameState.h PlayerInfo.cpp PlayerInfo.h)

target_include_directories(gamestate PUBLIC .)
target_link_libraries(gamestate basics)