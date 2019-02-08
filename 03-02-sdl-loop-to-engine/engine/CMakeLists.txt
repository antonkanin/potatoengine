cmake_minimum_required(VERSION 3.7)

project(engine)

add_library(${PROJECT_NAME}
        include/engine.h
        include/game_object.h

        src/engine.cxx
        src/game_object.cxx
        src/input_manager.cxx
        src/engine_sdl.cxx

        include/input_manager.h
        include/key_code.h
        include/engine_utils.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)