cmake_minimum_required(VERSION 2.8)

project(hs_game)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable(hs_game hs_game_main.cpp)
install(TARGETS hs_game DESTINATION "bin")

