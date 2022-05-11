cmake_minimum_required(VERSION 3.15)
project(VLVector)

set(CMAKE_CXX_STANDARD 14)

add_executable(VLVector main.cpp VLVector.hpp vl_string.h vl_vector.h)