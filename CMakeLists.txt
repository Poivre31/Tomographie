cmake_minimum_required(VERSION 3.23)

project(IRM)

add_executable(IRM)
target_sources(IRM PUBLIC main.cpp data/image.cpp data/complex_matrix.cpp)
target_include_directories(IRM PUBLIC data math radon)
