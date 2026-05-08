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
    complex_matrix(complex_matrix &im);
    complex_matrix(image im);

    size_t width();

    size_t height();

    /// @brief Returns the pixel value at (`x`,`y`)
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    complex get(size_t x, size_t y);

    /// @brief Sets the pixel value at (`x`,`y`) to `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    void set(size_t x, size_t y, complex value);

    /// @brief Increments the pixel value at (`x`,`y`) by `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    void increment(size_t x, size_t y, complex value);

    std::vector<complex> get_column(size_t x);
    std::vector<complex> get_line(size_t y);
    void set_column(std::vector<complex> data, size_t x);
    void set_line(std::vector<complex> data, size_t y);

    void rotate(int dx, int dy)
    {
        complex_matrix temp(*this);
        for (size_t i = 0; i < _width; i++)
        {
            for (size_t j = 0; j < _height; j++)
            {
                size_t x = ((int)i - dx) % _width + 1;
                size_t y = ((int)j - dy) % _width + 1;
                temp.set(i + 1, j + 1, get(x, y));
            }
        }

        for (size_t i = 0; i < _width; i++)
        {
            for (size_t j = 0; j < _height; j++)
            {
                set(i + 1, j + 1, temp.get(i + 1, j + 1));
            }
        }
    }

    image real_part_to_image();

    image imag_part_to_image();

    image modulus_to_image();

    image phase_to_image();

private:
    size_t _width;
    size_t _height;
    std::shared_ptr<complex[]> _data;
};