cmake_minimum_required(VERSION 3.20)
project(type_lists)

set(CMAKE_CXX_STANDARD 17)

add_executable(type_lists main.cpp tests.cpp type-lists.hxx "tests.cpp")
