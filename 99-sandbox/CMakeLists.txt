cmake_minimum_required(VERSION 3.7)

project(99-sandbox)

add_executable(${PROJECT_NAME}
        main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if (MINGW)
    target_link_libraries(${PROJECT_NAME}
            -lmingw32
            SDL2main
            SDL2
            -mwindows
            -lopengl32)
else()
    target_link_libraries(${PROJECT_NAME} SDL2 GL)
endif()

if (MINGW)
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            C:\\msys64\\mingw64\\include\\bullet
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
            )
else()
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            /usr/include/bullet)
endif()


