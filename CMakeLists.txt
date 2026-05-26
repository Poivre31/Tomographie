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
    utility/exemples.h
)


add_executable(sinogram generate_sinogram.cpp)
target_link_libraries(sinogram PRIVATE lib)

add_executable(reconstruct reconstruct_image.cpp)
target_link_libraries(reconstruct PRIVATE lib)

add_executable(validation validation.cpp)
target_link_libraries(validation PRIVATE lib)

# add_executable(gui gui.cpp)
# target_include_directories(gui PRIVATE extern/imgui extern/imgui/backends)
# target_sources(gui PRIVATE
#     extern/imgui/imgui.cpp
#     extern/imgui/imgui_demo.cpp
#     extern/imgui/imgui_draw.cpp
#     extern/imgui/imgui_tables.cpp
#     extern/imgui/imgui_widgets.cpp
#     extern/imgui/imconfig.h
#     extern/imgui/imgui.h
#     extern/imgui/imgui_internal.h
#     extern/imgui/imstb_rectpack.h
#     extern/imgui/imstb_textedit.h
#     extern/imgui/imstb_truetype.h

#     extern/imgui/backends/imgui_impl_sdl2.cpp
#     extern/imgui/backends/imgui_impl_opengl3.cpp

# )

# find_package(X11 REQUIRED)
# find_package(SDL2 REQUIRED)
# find_package(OpenGL REQUIRED)

# target_link_libraries(gui PUBLIC
#     SDL2::SDL2
#     OpenGL::GL
#     ${X11_LIBRARIES}
# )

target_include_directories(lib PRIVATE data math radon utility)
target_include_directories(sinogram PRIVATE data math radon utility)
target_include_directories(reconstruct PRIVATE data math radon utility)
target_include_directories(validation PRIVATE data math radon utility)

target_compile_options(lib PUBLIC -O3 -march=native -flto)
target_compile_options(sinogram PUBLIC -O3 -march=native -flto)
target_compile_options(reconstruct PUBLIC -O3 -march=native -flto)
target_compile_options(validation PUBLIC -O3 -march=native -flto)
