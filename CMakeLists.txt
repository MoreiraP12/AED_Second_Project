cmake_minimum_required(VERSION 3.17)
project(aed_proj_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2 main.cpp
        src/Menu.cpp
        src/Input.cpp
        src/Stop.h src/Stop.cpp
        src/data.cpp src/data.h
        src/graph.h src/graph.cpp
        cmake-build-debug/dataset src/Exceptions.h src/ShowStop.h)