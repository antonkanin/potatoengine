cmake_minimum_required(VERSION 3.9)

project(01-03-hello-lib-dynamic)

add_executable(01-03-hello-lib-dynamic main.cxx)

# adding '-ldl' to link dlopen function, we are only doing this for the gnu compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif()




