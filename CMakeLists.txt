cmake_minimum_required(VERSION 3.23)

project(IRM)

add_executable(IRM)
target_sources(IRM PUBLIC main.cpp image.cpp complex_matrix.cpp)
