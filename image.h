#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

class image
{
public:
    image(size_t width, size_t height);

    ~image();

    // Image should always be passed by reference
    image(const image &) = delete;

    size_t width();

    size_t height();

    /// @brief Returns the pixel value at (`x`,`y`)
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    double get(size_t x, size_t y);

    /// @brief Sets the pixel value at (`x`,`y`) to `value`
    /// @param x horizontal position, from one to width / left to right
    /// @param y vertical position, from one to height / top to bottom
    void set(size_t x, size_t y, double value);

    /// @brief Saves the image to `path` as a txt file containing line by line: width, then height, then all values in row major order
    /// @param path without the extension
    void save(std::string path);

    /// @brief Fills the entire image with `value`
    void fill_uniform(double value);

    /// @brief Draws an axis oriented box centered in `(x0,y0)`
    /// @param add If set to `true`, add `value` to the current data instead of replacing it
    void fill_rectangle(double value, size_t x0, size_t y0, size_t width, size_t height, bool add = true);

    /// @brief Draws an axis oriented ellipse centered in `(x0,y0)`
    /// @param a Horizontal semi-axis (half of the width)
    /// @param b Vertical semi-axis (half of the height)
    /// @param add If set to `true`, add `value` to the current data instead of replacing it
    void fill_ellipse(double value, size_t x0, size_t y0, size_t a, size_t b, bool add = true);

    /// @brief Draws a modified Shepp-Logan phantom reference image centered in `(x0,y0)` with height `size`
    void fill_phantom(size_t x0, size_t y0, size_t size, bool high_contrast = true, bool overwrite = true);

private:
    size_t _width;
    size_t _height;
    double *_data = nullptr;
};