cmake_minimum_required(VERSION 3.20)
project(type_lists)

set(CMAKE_CXX_STANDARD 23)

add_executable(type_lists main.cpp tests.cpp tests.hxx type-lists.hxx)
