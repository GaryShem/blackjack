project(cards)

add_library(cards STATIC Card.cpp Card.h CardShoe.cpp CardShoe.h Hand.cpp Hand.h json.hpp)

target_include_directories(cards PUBLIC .)