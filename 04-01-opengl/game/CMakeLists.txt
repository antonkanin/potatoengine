cmake_minimum_required(VERSION 3.7)

project(04-01-game-opengl)

add_executable(${PROJECT_NAME}
        game.cpp
        game_objects/space_ship.hpp
        game_objects/camera_keyboard_controller.hpp
        game_objects/camera_gui_controller.hpp
        game_objects/show_fps.hpp
        game_objects/vehicle.hpp
        game_objects/light_controller.hpp
        game_objects/audio_test.hpp

        game_objects/cube.hpp

        game_objects/editor/object_selector.hpp
        game_objects/editor/object_creator.hpp
        game_objects/editor/mode_switcher.hpp

        game_objects/game/player.hpp
        game_objects/game/enemy.hpp
        game_objects/game/enemy.cpp
        game_objects/game/enemies_spawer.hpp

        game_objects/utils.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} 04-01-engine)

###############################################################################
# copying shaders
configure_file(../engine/src/renderer/shaders/generic_shader.vert
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/generic_shader.vert COPYONLY)

configure_file(../engine/src/renderer/shaders/generic_shader.frag
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/generic_shader.frag COPYONLY)

configure_file(../engine/src/renderer/shaders/light_shader.vert
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/light_shader.vert COPYONLY)

configure_file(../engine/src/renderer/shaders/light_shader.frag
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/light_shader.frag COPYONLY)


###############################################################################
# copying levels
configure_file(scenes/level01.yaml
        ${CMAKE_CURRENT_BINARY_DIR}/scenes/level01.yaml COPYONLY)


###############################################################################
# copying resourses (models, audio, textures)
file(GLOB resources "res/*")
file(COPY ${resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
