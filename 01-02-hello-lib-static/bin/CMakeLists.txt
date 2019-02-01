cmake_minimum_required(VERSION 3.9)

project(01-02-hello-lib-static-main)

add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} PUBLIC 01-02-hello-lib-static-library)