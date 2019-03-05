cmake_minimum_required(VERSION 3.7)

project(external)

file(GLOB_RECURSE ext_source
        ${PROJECT_SOURCE_DIR}/imgui/*.cpp
        ${PROJECT_SOURCE_DIR}/imgui/*.h

        ${PROJECT_SOURCE_DIR}/picopng/*.h)

add_library(${PROJECT_NAME} STATIC ${ext_source})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/imgui/
        ${PROJECT_SOURCE_DIR}/picopng/)

