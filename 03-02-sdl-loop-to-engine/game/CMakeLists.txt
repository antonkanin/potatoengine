cmake_minimum_required(VERSION 3.7)

project(game)

add_executable(${PROJECT_NAME}
        game.cxx
        input_printer.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} engine)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include)