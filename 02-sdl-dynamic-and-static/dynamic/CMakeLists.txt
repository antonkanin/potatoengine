# this config assumes that SDL2 has been installed in the system, either manually (compile sources -> make install)
# or as a package (i.e. sudo dnf install SDL2-devel on Fedora)

cmake_minimum_required(VERSION 3.7)

project(02-01-sdl-test-dynamic)

add_executable(${PROJECT_NAME} ../src/main.cxx)

target_link_libraries(${PROJECT_NAME} SDL2)