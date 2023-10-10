#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (foobar C)

#positionne la variable
set (CMAKE_C_FLAGS "-std=c99 -g -Wall")

#définit le nom du programme ainsi que ses sources
add_executable(foobar foobar.c foo.c bar.c)

#definie les bibliothèques
target_link_libraries(foobar m)