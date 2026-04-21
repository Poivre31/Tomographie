#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

class image {
    public:
    image(size_t width,size_t height);

    ~image();

    size_t width();

    size_t height();

    /// @brief Returns the pixel value at (`x`,`y`)
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    /// @return 
    double get(size_t x, size_t y);

    /// @brief Sets the pixel value at (`x`,`y`) to `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    /// @return 
    void set(size_t x, size_t y, double value);

    /// @brief Saves the image to `path`
    /// @param path without the extension
    void save(std::string path);

    void fill_rectangle(double value, size_t x0, size_t y0, size_t width, size_t height, bool add = true);
    void fill_ellipse(double value, size_t x0, size_t y0, size_t width, size_t height, bool add = true);

    private:
    size_t _width;
    size_t _height;
    double* _data=nullptr;
};