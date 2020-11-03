project(pimpl)

add_library(pimpl ConsolePlayer.cpp ConsolePlayer.h)

target_include_directories(pimpl PUBLIC .)

target_link_libraries(pimpl players)