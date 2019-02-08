cmake_minimum_required(VERSION 3.7)

project(03-02-sdl-loop-to-engine)

add_executable(${PROJECT_NAME}
        game/game.cxx
        game/input_printer.h

        engine/include/engine.h
        engine/include/game_object.h

        engine/src/engine.cxx
        engine/src/game_object.cxx
        engine/src/input_manager.cxx
        engine/src/engine_sdl.cxx

        engine/include/input_manager.h
        engine/include/key_code.h
        engine/include/engine_utils.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include)