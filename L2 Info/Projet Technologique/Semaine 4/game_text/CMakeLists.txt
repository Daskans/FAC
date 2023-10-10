#version minimale
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (game C)

#définition variable
set (CMAKE_C_FLAGS "-std=c99 -g -Wall")

link_directories(${CMAKE_SOURCE_DIR})

#ajout des executables
add_executable(game_text game_text.c)

#definie les bibliothèques
target_link_libraries(game_text game m)
