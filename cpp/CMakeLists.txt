cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
# Install prefix has to be set prior to project(-) and
#   the CACHE PATH has to be there to update the cache
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}" CACHE PATH "PI_INSTALL_PREIFX")

project(pi_projects)

add_subdirectory(01.hangman)
add_subdirectory(02.hs_game)


