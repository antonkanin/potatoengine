cmake_minimum_required(VERSION 3.9)

project(01-02-hello-lib-static-library)
        
add_library(01-02-hello-lib-static-library STATIC src/hellolib.cxx include/hellolib.h)
target_include_directories(01-02-hello-lib-static-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)