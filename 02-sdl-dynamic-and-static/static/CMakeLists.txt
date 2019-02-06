cmake_minimum_required(VERSION 3.7)

project(02-02-sdl-test-static)

add_executable(${PROJECT_NAME} ../src/main.cxx)

target_link_libraries(${PROJECT_NAME} -ldl -pthread libSDL2.a)