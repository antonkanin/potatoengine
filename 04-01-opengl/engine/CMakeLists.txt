cmake_minimum_required(VERSION 3.7)

project(04-01-engine)

add_library(${PROJECT_NAME} STATIC
        src/engine.cpp
        src/game_object.cpp
        src/input_manager.cpp
        src/mesh.cpp
        src/movable_object.cpp
        src/mesh.cpp
        src/model.cpp
        src/file_utils.cpp
        src/engine_utils.cpp
        src/log_utils.cpp
        src/game_objects_list.cpp

        src/input_component.cpp
        src/video_component.cpp
        src/gui_component.cpp
        src/physics_component.cpp
        src/audio_component.cpp

        src/renderer/program.cpp
        src/renderer/shader.cpp
        src/renderer/opengl_utils.cpp
        src/renderer/debug_drawer.cpp

        src/imgui/imgui_impl_sdl.cpp
        src/imgui/imgui_impl_opengl3.cpp

        src/renderer/debug_drawer.hpp

        src/stb_image.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

if (MINGW)
    target_link_libraries(${PROJECT_NAME}
        SDL2_mixer
            -lmingw32
            -lSDL2main
            -lSDL2
            -mwindows
            -lopengl32

            #        GL
#        stbi
        assimp
        external
        BulletDynamics
        BulletCollision
        LinearMath
        yaml-cpp)
else()
    target_link_libraries(${PROJECT_NAME}
            SDL2
            SDL2_mixer
            GL
            stbi
            assimp
            external
            BulletDynamics
            BulletCollision
            LinearMath
            yaml-cpp)
endif()

if (MINGW)
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            C:\\msys64\\mingw64\\include\\bullet
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
            )
else()
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            /usr/include/bullet)
endif()


