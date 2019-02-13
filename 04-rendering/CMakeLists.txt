cmake_minimum_required(VERSION 3.7)

project(04-rendering)

add_executable(${PROJECT_NAME}
        main.cpp
        draw_utils.cpp
        image.cpp
        point.cpp
        point_array.cpp
        draw_line_tests.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)