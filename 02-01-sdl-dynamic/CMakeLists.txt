cmake_minimum_required(VERSION 3.7)

project(02-01-sdl-dynamic)

add_executable(${PROJECT_NAME} main.cxx)

target_link_libraries(${PROJECT_NAME} SDL2)