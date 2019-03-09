cmake_minimum_required(VERSION 3.7)

project(05-audio)

add_executable(${PROJECT_NAME}
        main_audio.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} SDL2)

configure_file(${PROJECT_SOURCE_DIR}/Alesis-Fusion-Nylon-String-Guitar-C4.wav
        ${CMAKE_CURRENT_BINARY_DIR}/Alesis-Fusion-Nylon-String-Guitar-C4.wav COPYONLY)