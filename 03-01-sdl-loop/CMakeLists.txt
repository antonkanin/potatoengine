cmake_minimum_required(VERSION 3.7)

project(03-01-sdl-loop)

add_executable(${PROJECT_NAME} main.cxx)

target_link_libraries(${PROJECT_NAME} SDL2)