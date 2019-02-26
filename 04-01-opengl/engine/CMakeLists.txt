cmake_minimum_required(VERSION 3.7)

project(04-01-engine)

add_library(${PROJECT_NAME} SHARED
        src/engine.cpp
        src/game_object.cpp
        src/input_manager.cpp
        src/engine_sdl.cpp
        src/read_obj.cpp
        src/model.cpp
        src/texture_image.cpp
        src/renderer/renderer.cpp
        src/renderer/renderer_opengl.cpp
        src/renderer/shader.cpp
        src/renderer/opengl_utils.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2 GL)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)