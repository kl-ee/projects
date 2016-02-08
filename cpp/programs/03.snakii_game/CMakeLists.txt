cmake_minimum_required(VERSION 2.8)

project(snakii_game)
set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(snakii_game snakii_game_main.cpp)

target_link_libraries(snakii_game ncurses)

install(TARGETS snakii_game DESTINATION "bin")
