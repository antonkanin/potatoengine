cmake_minimum_required(VERSION 3.7)

project(04-01-game-opengl)

add_executable(${PROJECT_NAME}
        game.cpp
        space_ship.hpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} 04-01-engine)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src/renderer/shader01.vert
        ${CMAKE_CURRENT_BINARY_DIR}/shader01.vert)