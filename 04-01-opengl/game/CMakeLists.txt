cmake_minimum_required(VERSION 3.7)

project(04-01-game-opengl)

add_executable(${PROJECT_NAME}
        game.cpp
        game_objects/space_ship.hpp
        game_objects/camera_keyboard_controller.hpp
        game_objects/camera_gui_controller.hpp
        game_objects/show_fps.hpp
        game_objects/vehicle.hpp
        game_objects/light_controller.hpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} 04-01-engine)

###############################################################################
# copying shaders
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../engine/src/renderer/shader01.vert
        ${CMAKE_CURRENT_BINARY_DIR}/shader01.vert COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../engine/src/renderer/shader01.frag
        ${CMAKE_CURRENT_BINARY_DIR}/shader01.frag COPYONLY)

###############################################################################
# copying images and objs files

configure_file(res/cube/cube.obj
        ${CMAKE_CURRENT_BINARY_DIR}/res/cube/cube.obj COPYONLY)

configure_file(res/cube/cube.mtl
        ${CMAKE_CURRENT_BINARY_DIR}/res/cube/cube.mtl COPYONLY)


# figure
configure_file(res/figure.png
        ${CMAKE_CURRENT_BINARY_DIR}/res/figure.png COPYONLY)

configure_file(res/figure.mtl
        ${CMAKE_CURRENT_BINARY_DIR}/res/figure.mtl COPYONLY)

configure_file(res/figure.obj
        ${CMAKE_CURRENT_BINARY_DIR}/res/figure.obj COPYONLY)

configure_file(res/figure.blend
        ${CMAKE_CURRENT_BINARY_DIR}/res/figure.blend COPYONLY)

# two faces
configure_file(res/two_faces.obj
        ${CMAKE_CURRENT_BINARY_DIR}/res/two_faces.obj COPYONLY)

configure_file(res/two_faces.mtl
        ${CMAKE_CURRENT_BINARY_DIR}/res/two_faces.mtl COPYONLY)

# three faces
configure_file(res/three_faces.png
        ${CMAKE_CURRENT_BINARY_DIR}/res/three_faces.png COPYONLY)

configure_file(res/three_faces.obj
        ${CMAKE_CURRENT_BINARY_DIR}/res/three_faces.obj COPYONLY)

#vehicle
configure_file(res/military_vehicle_2.obj
        ${CMAKE_CURRENT_BINARY_DIR}/res/military_vehicle_2.obj COPYONLY)

configure_file(res/military_vehicle_2.mtl
        ${CMAKE_CURRENT_BINARY_DIR}/res/military_vehicle_2.mtl COPYONLY)

