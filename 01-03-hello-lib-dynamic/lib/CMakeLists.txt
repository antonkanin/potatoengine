cmake_minimum_required(VERSION 3.9)

project(01-03-hello-lib-dynamic-library)

add_library(${PROJECT_NAME} SHARED hellolib.cxx)

# TODO we referencing this library as hello.dll (libhello.so in linux) in the code
# perhaps we should turn it into a global parameter
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hello")