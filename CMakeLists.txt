cmake_minimum_required(VERSION 3.20)
project(2dtest C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Sorgenti ---
file(GLOB_RECURSE SOURCES src/*.c)

# --- Eseguibile ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Include dirs ---
target_include_directories(${PROJECT_NAME} PRIVATE src)

# --- SDL2 ---
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# --- Warning ---
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wno-unused-parameter)

# --- Output nella root ---
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)
