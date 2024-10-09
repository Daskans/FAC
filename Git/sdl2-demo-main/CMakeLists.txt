cmake_minimum_required(VERSION 3.0)

project ("demo_sdl2" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

## find SDL2
include(sdl2.cmake)
message(STATUS "SDL2 include dir: ${SDL2_ALL_INC}")
message(STATUS "SDL2 all libraries: ${SDL2_ALL_LIBS}")

## compilation rules
include_directories(${SDL2_ALL_INC})
add_executable(minimal minimal.c)
target_link_libraries(minimal ${SDL2_ALL_LIBS} m)
add_executable(demo main.c demo.c)
target_link_libraries(demo ${SDL2_ALL_LIBS} m)
add_executable(model main.c model.c)
target_link_libraries(model ${SDL2_ALL_LIBS} m)

## copy useful ressources in the build directory
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
