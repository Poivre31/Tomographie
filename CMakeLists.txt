cmake_minimum_required(VERSION 3.23)

project(IRM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(lib STATIC
    data/complex_matrix.cpp
    data/complex_matrix.h
    data/image.cpp
    data/image.h

    math/my_dft.h
    math/my_fft.h
    math/my_random.h
    math/vec2.h
    math/complex.h
    math/bilinear_interp.h
    math/psnr.h
    math/ssim.cpp
    math/ssim.h

    radon/filters.cpp
    radon/filters.h
    radon/projection.cpp
    radon/projection.h
    radon/ray.h
    radon/sinogram.h

    utility/save.cpp
    utility/save.h
    utility/timer.h
    utility/config.h
)


add_executable(sinogram generate_sinogram.cpp)
target_link_libraries(sinogram PRIVATE lib)

add_executable(reconstruct reconstruct_image.cpp)
target_link_libraries(reconstruct PRIVATE lib)

target_include_directories(lib PRIVATE data math radon utility)
target_include_directories(sinogram PRIVATE data math radon utility)
target_include_directories(reconstruct PRIVATE data math radon utility)

target_compile_options(lib PUBLIC -O3 -march=native -flto)
target_compile_options(sinogram PUBLIC -O3 -march=native -flto)
target_compile_options(reconstruct PUBLIC -O3 -march=native -flto)

# add_executable(Sinogram generate_sinogram.cpp
#     math/my_dft.cpp)
# target_link_libraries(Sinogram PRIVATE lib)

# add_executable(Reconstuction reconstruct_image.cpp)
# target_link_libraries(Reconstuction PRIVATE lib)

# target_include_directories(Reconstuction PUBLIC data math radon utility)
# target_compile_options(Reconstuction PUBLIC -O3 -march=native -flto)

# if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_options(IRM PUBLIC
#         -flto
#         -fuse-ld=lld
#     )
# elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
# endif()
