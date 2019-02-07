cmake_minimum_required(VERSION 3.7)

project(03-01-sdl-loop)

add_executable(${PROJECT_NAME} main.cxx)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)