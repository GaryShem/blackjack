project(observer)

add_library(observer IUpdatable.cpp IUpdatable.h IUpdater.cpp IUpdater.h)

target_include_directories(observer PUBLIC .)