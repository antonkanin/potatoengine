cmake_minimum_required(VERSION 3.7)

project(04-01-engine)

add_library(${PROJECT_NAME} SHARED
        src/engine.cpp
        src/game_object.cpp
        src/input_manager.cpp
        src/engine_sdl.cpp
        src/renderer/renderer.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)

# TODO one day I need to separate PUBLIC and PRIVATE header files into separate directories
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)