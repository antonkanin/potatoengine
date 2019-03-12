cmake_minimum_required(VERSION 3.7)

project(04-01-engine)

add_library(${PROJECT_NAME} STATIC
        src/engine.cpp
        src/game_object.cpp
        src/input_manager.cpp
        src/engine_sdl.cpp
        src/read_obj.cpp
        src/mesh.cpp
        src/movable_object.cpp
        src/mesh.cpp
        src/model.cpp
        src/input_component.cpp
        src/video_component.cpp
        src/engine_utils.cpp

        src/renderer/renderer.cpp
        src/renderer/program.cpp
        src/renderer/renderer_opengl.cpp
        src/renderer/shader.cpp
        src/renderer/opengl_utils.cpp


        src/imgui/imgui_impl_sdl.cpp
        src/imgui/imgui_impl_opengl3.cpp

        src/renderer/debug_drawer.hpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME}
        SDL2
        GL
        stbi
        assimp
        external
        BulletDynamics
        BulletCollision
        LinearMath)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        /usr/include/bullet)