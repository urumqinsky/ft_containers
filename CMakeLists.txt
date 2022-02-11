cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(containers main.cpp Stack/Stack.hpp Vector/Vector.hpp Set/Set.hpp Map/Map.hpp)
