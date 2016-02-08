cmake_minimum_required(VERSION 2.8)

project(hangman)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable(hangman AttemptHandler.cpp DisplayHandler.cpp hangman_main.cpp)
install(TARGETS hangman DESTINATION "bin")

