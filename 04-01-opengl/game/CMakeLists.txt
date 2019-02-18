cmake_minimum_required(VERSION 3.7)

project(04-01-game-opengl)

add_executable(${PROJECT_NAME}
        game.cxx
        input_printer.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} 04-01-engine)