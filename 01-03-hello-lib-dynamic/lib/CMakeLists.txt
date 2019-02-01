cmake_minimum_required(VERSION 3.9)

project(01-03-hello-lib-dynamic-library)

add_library(01-03-hello-lib-dynamic-library SHARED hellolib.cxx)