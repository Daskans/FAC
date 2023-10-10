#verion minimale
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (tsp C)

#definie les variables
set(CMAKE_C_FLAGS "-std=c99 -Wall -g")

#ajoute une librairie
add_library(tsp matrice2d.c memoire.c tsp.c)

#definit le nom du programme et ses sources
add_executable(solve solve.c)
add_executable(convert convert.c)

#définie les bibliothèque
target_link_libraries(solve libm.a tsp m)
target_link_libraries(convert libm.a tsp m)