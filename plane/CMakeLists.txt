cmake_minimum_required(VERSION 3.19)
project(plane)

set(CMAKE_CXX_STANDARD 14)

add_executable(plane main.cpp Plane.cpp Plane.h function.h)