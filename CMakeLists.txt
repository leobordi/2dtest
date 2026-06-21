cmake_minimum_required(VERSION 3.16)
project(2dtest C)

find_package(SDL2 REQUIRED)

add_executable(2dtest 2dtest.c)

target_link_libraries(2dtest SDL2::SDL2 SDL2::SDL2main)
