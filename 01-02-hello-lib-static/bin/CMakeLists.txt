cmake_minimum_required(VERSION 3.9)

project(01-02-hello-lib-static-main)

add_executable(01-02-hello-lib-static-main main.cxx)
target_link_libraries(01-02-hello-lib-static-main PUBLIC 01-02-hello-lib-static-library)