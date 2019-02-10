cmake_minimum_required(VERSION 3.7)

project(04-rendering)

add_executable(${PROJECT_NAME}
        main.cxx
        image.cpp
        point.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)