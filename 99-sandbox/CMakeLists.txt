cmake_minimum_required(VERSION 3.7)

project(99-sandbox)

add_executable(${PROJECT_NAME}
        main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)