#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include "complex.h"
#include "image.h"

class complex_matrix
{
public:
    complex_matrix(size_t width, size_t height);
    complex_matrix(image im);
    const complex_matrix copy();

    size_t width();

    size_t height();

    /// @brief Returns the pixel value at (`x`,`y`)
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    const complex get(size_t x, size_t y);

    /// @brief Sets the pixel value at (`x`,`y`) to `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    void set(size_t x, size_t y, complex value);

    /// @brief Increments the pixel value at (`x`,`y`) by `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    void increment(size_t x, size_t y, complex value);

    const std::vector<complex> get_column(size_t x);
    const std::vector<complex> get_line(size_t y);
    void set_column(std::vector<complex> data, size_t x);
    void set_line(std::vector<complex> data, size_t y);

    const image real_part_to_image();

    const image imag_part_to_image();

    const image modulus_to_image();

    const image phase_to_image();

    void apply_elementwise(std::function<complex(complex)> f);

private:
    size_t _width;
    size_t _height;
    std::shared_ptr<complex[]> _data;
};