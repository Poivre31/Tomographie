cmake_minimum_required(VERSION 3.23)

project(IRM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(IRM)
target_sources(IRM PUBLIC main.cpp data/image.cpp data/complex_matrix.cpp)
target_include_directories(IRM PUBLIC data math radon utility)
target_compile_options(IRM PUBLIC -O3 -march=native -flto)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_options(IRM PUBLIC
        -flto
        -fuse-ld=lld
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif()
