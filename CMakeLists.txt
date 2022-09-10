cmake_minimum_required(VERSION 3.22.0)

project(my-cmake-project)
add_executable(Program main.cpp)
set_property(TARGET Program PROPERTY CXX_STANDARD 17)
