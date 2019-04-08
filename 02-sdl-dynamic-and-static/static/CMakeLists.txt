cmake_minimum_required(VERSION 3.7)

project(02-02-sdl-test-static)

add_executable(${PROJECT_NAME} ../src/main.cxx)

find_library(SDL2_LIB libSDL2.a)

if (MINGW)
    target_link_libraries(${PROJECT_NAME} -pthread "${SDL2_LIB}")
else()
    target_link_libraries(${PROJECT_NAME} -ldl -pthread "${SDL2_LIB}")
endif()